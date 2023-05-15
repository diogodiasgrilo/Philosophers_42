/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:24:39 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/15 19:32:01 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CANT USE EXIT

#include "../include/philos.h"

int	thinking_philo(t_philo *philo)
{
	if (!philo->last_meal)
		philo->last_meal = get_time(philo->p);
	if (write_message(philo, philo->thinking, 0))
		return (1);
	while (philo->n_phi > 1 && philo->l_fork->state != 0)
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo));
	pthread_mutex_lock(philo->l_fork->fork);
	philo->l_fork->state = 1;
	while (philo->r_fork->state != 0)
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo));
	pthread_mutex_lock(philo->r_fork->fork);
	philo->r_fork->state = 1;
	return (0);
}

int	eating_philo(t_philo *philo)
{
	int	check_dead;

	check_dead = 0;
	if (philo->t_m_eat)
	{
		philo->last_meal = get_time(philo->p);
		if (write_message(philo, philo->eating, 1))
			return (1);
		while (check_dead < philo->p->t_eat)
		{
			if (check_dead >= philo->p->t_die)
				return (write_dead(philo));
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
			return (write_dead(philo));
		counter = (get_time(philo->p) - start);
		check_dead = (get_time(philo->p) - philo->last_meal);
	}
	return (0);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	if (philo->p->n_phi > 1 && (philo->id) % 2 == 0)
		usleep(2);
	philo->last_meal = 0;
	while (!find_death(philo->p))
	{
		if (thinking_philo(philo))
			return (0);
		if (eating_philo(philo))
			return (0);
		if (philo->t_m_eat >= 0 && philo->p->t_all_eaten >= philo->p->n_phi
			* philo->t_m_eat)
			return (unlock(philo));
		if (sleeping_philo(philo))
			return (0);
	}
	return (unlock(philo));
}
