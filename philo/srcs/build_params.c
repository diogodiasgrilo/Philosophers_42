/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:31:11 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 16:55:47 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	prep_philos(t_prog *p, int i)
{
	p->philos[i]->p = p;
	p->philos[i]->id = i;
	p->philos[i]->dead = 0;
	p->philos[i]->last_meal = 0;
	p->philos[i]->t_counter = 0;
	p->philos[i]->t_m_eat = p->t_m_eat;
	p->philos[i]->times_eaten = 0;
	p->philos[i]->n_phi = p->n_phi;
	p->philos[i]->writing = &(p->writing);
	p->philos[i]->r_fork = p->forks[i];
	if (i + 1 == p->n_phi)
		p->philos[i]->l_fork = p->forks[(i + 1) % p->n_phi];
	else
		p->philos[i]->l_fork = p->forks[i + 1];
	p->philos[i]->num = ft_itoa(p->philos[i]->id + 1);
	p->philos[i]->thinking = ft_strjoin(p->philos[i]->num, " is thinking\n");
	p->philos[i]->eating = ft_strjoin(p->philos[i]->num, " is eating\n");
	p->philos[i]->sleeping = ft_strjoin(p->philos[i]->num, " is sleeping\n");
	p->philos[i]->died = ft_strjoin(p->philos[i]->num, " died\n");
}

void	*build_params(t_prog *p)
{
	p->n_phi = ft_atoi(p->argv[1]);
	p->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t) * p->n_phi);
	p->philos = (t_philo **)malloc(sizeof(t_philo) * p->n_phi);
	p->i = -1;
	while (++(p->i) < p->n_phi)
		p->forks[p->i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* p->n_phi);
	p->i = -1;
	while (++(p->i) < p->n_phi)
		p->philos[p->i] = (t_philo *)malloc(sizeof(t_philo));
	if (!p->forks || !p->philos)
		return (free_everything(p));
	p->t_die = ft_atoi(p->argv[2]);
	p->t_eat = ft_atoi(p->argv[3]);
	p->t_sleep = ft_atoi(p->argv[4]);
	if (p->argc == 6)
		p->t_m_eat = ft_atoi(p->argv[5]);
	else
		p->t_m_eat = -1;
	p->i = -1;
	while (++(p->i) < p->n_phi)
		prep_philos(p, p->i);
	return (p);
}
