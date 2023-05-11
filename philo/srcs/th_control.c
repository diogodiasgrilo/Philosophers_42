/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:32:53 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/11 10:48:43 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	get_time(t_prog *p)
{
	gettimeofday(&(p->current_time), NULL);
	p->elapsed_time = (p->current_time.tv_sec - p->start_time.tv_sec) + \
		(p->current_time.tv_usec - p->start_time.tv_usec) / 1000000.0;
}

void	start_threads(t_prog *p)
{
	int	i;

	gettimeofday(&(p->start_time), NULL);
	mutex_manager(p, 1);
	p->begin = 0;
	i = -1;
	while (++i < p->n_phi)
		prep_philos(p, i);
	i = -1;
	while (++i < p->n_phi)
		if (pthread_create(&(p->philos[i].th), NULL, \
			&routine, &p->philos[i]) != 0)
			write(2, "Failed to create thread!\n", 26);
	p->begin = 1;
	i = -1;
	while (++i < p->n_phi)
		if (pthread_join(p->philos[i].th, 0))
			write(2, "Failed to join thread!\n", 24);
	mutex_manager(p, 0);
}

void	mutex_manager(t_prog *p, int action)
{
	int	i;

	i = -1;
	if (action)
	{
		while (++i < p->n_phi)
			pthread_mutex_init(p->forks + i, 0);
		pthread_mutex_init(&p->writing, 0);
	}
	else
	{
		while (++i < p->n_phi)
			pthread_mutex_destroy(&p->forks[i]);
		pthread_mutex_destroy(&p->writing);
	}
}
