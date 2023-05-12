/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:32:53 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 16:33:00 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	get_time(t_prog *p)
{
	struct timeval	current_time;
	long			seconds;
	long			microseconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - p->start_time.tv_sec;
	microseconds = current_time.tv_usec - p->start_time.tv_usec;
	p->elapsed_time = (seconds * 1000) + (microseconds / 1000);
}

void	mutex_manager(t_prog *p, int action)
{
	int	i;

	i = -1;
	if (action)
	{
		while (++i < p->n_phi)
			pthread_mutex_init(p->forks[i], 0);
		pthread_mutex_init(&p->writing, 0);
	}
	else
	{
		while (++i < p->n_phi)
			pthread_mutex_destroy(p->forks[i]);
		pthread_mutex_destroy(&p->writing);
	}
}

void	start_threads(t_prog *p)
{
	int	i;

	gettimeofday(&(p->start_time), NULL);
	mutex_manager(p, 1);
	i = -1;
	while (++i < p->n_phi)
		if (pthread_create(&(p->philos[i]->th), NULL, &routine,
				p->philos[i]) != 0)
			ft_printf("Failed to create thread!\n");
	p->begin = 1;
	i = -1;
	while (++i < p->n_phi)
		if (pthread_join(p->philos[i]->th, 0))
			ft_printf("Failed to join thread!\n");
	mutex_manager(p, 0);
}
