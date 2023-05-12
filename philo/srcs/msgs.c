/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:36:30 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 17:21:21 by diogpere         ###   ########.fr       */
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

void	write_message(t_philo *philo, char *msg, int eating)
{
	int	time;

	if (eating)
		philo->times_eaten++;
	pthread_mutex_lock(philo->writing);
	if (!find_death(philo->p))
	{
		get_time(philo->p);
		time = philo->p->elapsed_time;
		ft_printf("%dms ", time);
		ft_printf("%s", msg);
	}
	pthread_mutex_unlock(philo->writing);
}

void	*small_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*write_dead(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->writing);
	if (!find_death(philo->p))
	{
		get_time(philo->p);
		time = philo->p->elapsed_time;
		ft_printf("%dms ", time);
		ft_printf("%s", philo->died);
	}
	philo->dead = 1;
	pthread_mutex_unlock(philo->writing);
	return (small_r(philo));
}
