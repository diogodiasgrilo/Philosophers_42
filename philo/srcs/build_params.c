/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:31:11 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/08 18:56:05 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	build_params(t_prog *p)
{
	p->n_phi = ft_atoi(p->argv[1]);
	p->th = (pthread_t *)malloc(sizeof(pthread_t) * (p->n_phi + 1));
	p->th[p->n_phi] = 0;
	p->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p->n_phi);
	p->philos = (t_philo *)ft_calloc(sizeof(t_philo), p->n_phi);
	if (!p->th || !p->forks || !p->philos)
		clear_and_exit(p);
	p->t_die = ft_atoi(p->argv[2]);
	p->t_eat = ft_atoi(p->argv[3]);
	p->t_sleep = ft_atoi(p->argv[4]);
	if (p->argc == 6)
		p->t_m_eat = ft_atoi(p->argv[5]);
}