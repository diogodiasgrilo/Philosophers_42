/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:24:39 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/18 17:21:47 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CANT USE EXIT

#include "../include/philos.h"

int	check_state(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->locks);
	if (!fork)
	{
		if (philo->r_fork->state != 0)
		{
			pthread_mutex_unlock(philo->locks);
			return (1);
		}
	}
	else
	{
		if (philo->l_fork->state != 0)
		{
			pthread_mutex_unlock(philo->locks);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->locks);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
		return (grabs_right_first(philo));
	else
		return (grabs_left_first(philo));
}

int	eating_philo(t_philo *philo)
{
	int	check_dead;

	check_dead = 0;
	while (philo->t_m_eat == 0)
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
	if (philo->t_m_eat)
	{
		philo->last_meal = get_time(philo->p);
		if (write_message(philo, philo->eating, 1))
			return (1);
		while (check_dead < philo->p->t_eat)
		{
			if (check_dead >= philo->p->t_die)
				return (write_dead(philo, get_time(philo->p)));
			check_dead = (get_time(philo->p) - philo->last_meal);
		}
		unlock(philo);
	}
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	int	start;
	int	counter;
	int	check_dead;

	check_dead = 0;
	counter = check_dead;
	start = get_time(philo->p);
	if (write_message(philo, philo->sleeping, 0))
		return (1);
	while (counter < philo->p->t_sleep)
	{
		if (check_dead >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
		counter = (get_time(philo->p) - start);
		check_dead = (get_time(philo->p) - philo->last_meal);
	}
	return (0);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	if ((philo->id + 1) % 2 == 0)
		(usleep(100));
	while (1)
	{
		if (thinking_philo(philo))
		{
			if ((philo->id + 1) % 2 == 0)
			{
				pthread_mutex_lock(philo->locks);
				if (philo->r_fork->state == 1)
				{	
					pthread_mutex_unlock(philo->r_fork->fork);
				}
				pthread_mutex_unlock(philo->locks);
			}	
			else
				pthread_mutex_unlock(philo->l_fork->fork);
			return (0);
		}
		if (eating_philo(philo))
		{
			unlock(philo);
			return (0);
		}
		pthread_mutex_lock(&philo->p->all_eaten);
		if (philo->t_m_eat >= 0 && philo->p->t_all_eaten >= philo->p->n_phi
			* philo->t_m_eat)
		{
			pthread_mutex_unlock(&philo->p->all_eaten);
			return (0);
		}
		pthread_mutex_unlock(&philo->p->all_eaten);
		if (sleeping_philo(philo))
			return (0);
	}
	return (0);
}
