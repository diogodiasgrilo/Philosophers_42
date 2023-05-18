/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:36:30 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/18 19:40:33 by diogpere         ###   ########.fr       */
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
		{
			pthread_mutex_lock(&philo->p->all_eaten);
			philo->p->t_all_eaten++;
			pthread_mutex_unlock(&philo->p->all_eaten);
		}
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
	return (1);
}

int	grabs_right_first(t_philo *philo)
{
	if (write_message(philo, philo->thinking, 0))
		return (1);
	while (philo->n_phi < 2 || check_state(philo, 0))
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
	pthread_mutex_lock(philo->locks);
	philo->r_fork->state = 1;
	pthread_mutex_unlock(philo->locks);
	pthread_mutex_lock(philo->r_fork->fork);
	while (check_state(philo, 1))
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
	pthread_mutex_lock(philo->locks);
	philo->l_fork->state = 1;
	pthread_mutex_unlock(philo->locks);
	pthread_mutex_lock(philo->l_fork->fork);
	return (0);
}

int	grabs_left_first(t_philo *philo)
{
	if (write_message(philo, philo->thinking, 0))
		return (1);
	while (philo->n_phi < 2 || check_state(philo, 1))
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
	pthread_mutex_lock(philo->locks);
	philo->l_fork->state = 1;
	pthread_mutex_unlock(philo->locks);
	pthread_mutex_lock(philo->l_fork->fork);
	while (check_state(philo, 0))
		if ((get_time(philo->p) - philo->last_meal) >= philo->p->t_die)
			return (write_dead(philo, get_time(philo->p)));
	pthread_mutex_lock(philo->locks);
	philo->r_fork->state = 1;
	pthread_mutex_unlock(philo->locks);
	pthread_mutex_lock(philo->r_fork->fork);
	return (0);
}
