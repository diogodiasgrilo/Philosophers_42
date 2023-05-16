/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:36:30 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/16 11:56:12 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	find_death(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phi)
		if (p->philos[i]->dead)
			return (1);
	return (0);
}

int	write_message(t_philo *philo, char *msg, int eating)
{
	pthread_mutex_lock(philo->writing);
	if (!find_death(philo->p))
	{
		if (eating)
			philo->p->t_all_eaten++;
		if (!find_death(philo->p))
		{
			printf("%d %s", get_time(philo->p), msg);
			pthread_mutex_unlock(philo->writing);
			return (0);
		}
	}
	pthread_mutex_unlock(philo->writing);
	return (1);
}

int	write_dead(t_philo *philo, int time)
{
	pthread_mutex_lock(philo->writing);
	if (!find_death(philo->p))
	{
		printf("%d %s", time, philo->died);
		philo->dead = 1;
	}
	pthread_mutex_unlock(philo->writing);
	unlock(philo);
	return (1);
}
