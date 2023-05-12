/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:24:39 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 17:22:03 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CANT USE EXIT

#include "../include/philos.h"

void	sleep_now(t_philo *philo, int duration, int option)
{
	usleep(duration);
	philo->last_meal += duration;
	if (option)
		philo->t_counter += duration;
}

int	thinking_philo(t_philo *philo)
{
	if (!find_death(philo->p))
	{
		write_message(philo, philo->thinking, 0);
		while (1)
		{
			if (philo->n_phi > 1 && \
				!pthread_mutex_lock(philo->l_fork) \
					&& !pthread_mutex_lock(philo->r_fork))
				break ;
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			if (philo->last_meal >= philo->p->t_die)
			{
				write_dead(philo);
				return (1);
			}
			else
				sleep_now(philo, 1, 1);
		}
	}
	if (philo->last_meal >= philo->p->t_die)
	{
		write_dead(philo);
		return (1);
	}
	return (0);
}

int	eating_philo(t_philo *philo)
{
	if (philo->t_m_eat && !find_death(philo->p))
	{
		philo->last_meal = 0;
		write_message(philo, philo->eating, 1);
		philo->t_counter = 0;
		while (philo->t_m_eat && \
			philo->t_counter < philo->p->t_eat)
		{
			if (philo->last_meal >= philo->p->t_die)
			{
				write_dead(philo);
				return (1);
			}
			else
				sleep_now(philo, 1, 1);
		}
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	if (philo->last_meal >= philo->p->t_die)
	{
		write_dead(philo);
		return (1);
	}
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	if (!find_death(philo->p))
	{
		write_message(philo, philo->sleeping, 0);
		philo->t_counter = 0;
		while (philo->t_counter < philo->p->t_sleep)
		{
			if (philo->last_meal >= philo->p->t_die)
			{
				write_dead(philo);
				return (1);
			}
			else
				sleep_now(philo, 1, 1);
		}
	}
	if (philo->last_meal >= philo->p->t_die)
	{
		write_dead(philo);
		return (1);
	}
	return (0);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
		if (philo->p->begin)
			break ;
	if ((philo->id) % 2 == 0)
		sleep_now(philo, 10, 1);
	while (!find_death(philo->p))
	{
		if (thinking_philo(philo))
			return (0);
		if (eating_philo(philo))
			return (0);
		// Wait for everyone to finish eating the number of times before returning
		if (philo->times_eaten >= philo->t_m_eat && philo->t_m_eat >= 0)
			return (small_r(philo));
		if (sleeping_philo(philo))
			return (0);
	}
	return (small_r(philo));
}
