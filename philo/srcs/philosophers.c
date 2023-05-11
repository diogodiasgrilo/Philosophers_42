/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:24:39 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/11 10:48:39 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CANT USE EXIT

#include "../include/philos.h"

void	sleep_now(t_philo *philo, int duration, int option)
{
	usleep(duration);
	philo->last_meal += duration;
	if (option)
		philo->t_counter += 9;
}

int	thinking_philo(t_philo *philo)
{
	if (!find_death(philo->p))
		write_message(philo, philo->thinking, 0);
	while (1)
	{
		if (philo->p->n_phi > 1 && \
			!pthread_mutex_lock(&philo->p->forks[philo->id]) \
			&& !pthread_mutex_lock(&philo->p->forks[(philo->id + 1) \
			% philo->p->n_phi]))
			break ;
		if (philo->last_meal >= philo->p->t_die)
		{
			(write_dead(philo));
			return (1);
		}
		else
			sleep_now(philo, 9, 0);
	}
	return (0);
}

int	eating_philo(t_philo *philo)
{
	if (philo->p->t_m_eat && !find_death(philo->p))
		write_message(philo, philo->eating, 1);
	philo->t_counter = 0;
	while (philo->p->t_m_eat && !find_death(philo->p) \
		&& philo->t_counter <= philo->p->t_eat)
	{
		if (philo->last_meal >= philo->p->t_die)
		{
			(write_dead(philo));
			return (1);
		}
		else
			sleep_now(philo, 9, 1);
	}
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	philo->t_counter = 0;
	if (!find_death(philo->p))
		write_message(philo, philo->sleeping, 0);
	while (!find_death(philo->p) && philo->t_counter < philo->p->t_sleep)
	{
		if (philo->last_meal >= philo->p->t_die)
		{
			(write_dead(philo));
			return (1);
		}
		else
			sleep_now(philo, 9, 1);
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
	while (!find_death(philo->p))
	{
		if ((philo->id) % 2 == 0)
			sleep_now(philo, 9, 0);
		if (thinking_philo(philo))
			return (0);
		if (eating_philo(philo))
			return (0);
		if (philo->times_eaten >= philo->p->t_m_eat)
			return (small_r(philo));
		philo->last_meal = 0;
		pthread_mutex_unlock(&philo->p->forks[philo->id]);
		pthread_mutex_unlock(&philo->p->forks[(philo->id + 1) \
			% philo->p->n_phi]);
		sleeping_philo(philo);
	}
	return (small_r(philo));
}
