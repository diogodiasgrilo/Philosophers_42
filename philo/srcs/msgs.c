/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:36:30 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/11 10:36:50 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	find_death(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phi)
		if (p->philos[i].dead)
			return (1);
	return (0);
}

void	write_message(t_philo *philo, char *msg, int eating)
{
	if (eating)
		philo->times_eaten++;
	pthread_mutex_lock(&philo->p->writing);
	if (!find_death(philo->p))
		write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&philo->p->writing);
}

void	*small_r(t_philo *philo)
{
	pthread_mutex_unlock(&philo->p->forks[philo->id]);
	pthread_mutex_unlock(&philo->p->forks[(philo->id) + 1 % philo->p->n_phi]);
	return (0);
}

void	*write_dead(t_philo *philo)
{
	philo->dead = 1;
	pthread_mutex_lock(&philo->p->writing);
	write(1, philo->died, ft_strlen(philo->died));
	pthread_mutex_unlock(&philo->p->writing);
	return (small_r(philo));
}
