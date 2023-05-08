/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:24:39 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/08 18:44:19 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CANT USE EXIT

#include "../include/philo.h"

void	get_time(t_prog	*p)
{
	gettimeofday(&(p->current_time), NULL);
	p->elapsed_time = (p->current_time.tv_sec - p->start_time.tv_sec) + 
		(p->current_time.tv_usec - p->start_time.tv_usec) / 1000000.0;
}

void	write_message(t_prog *p, char *num, char *msg)
{
	p->writing = 1;
	write(1, num, 1);
	write(1, msg, ft_strlen(msg));
	p->writing = 0;
}

void	*small_r(char *num)
{
	free(num);
	return (0);
}

void	*routine(void *prog)
{
	t_prog	*p;
	int		count;
	char	*num;
	
	p = (t_prog *)prog;
	num = ft_itoa(p->i + 1);
	while (!p->one_dead)
	{
		if (p->i % 2 != 0)
			usleep(1);
		// ALSO CHECK HERE IF HE'S DIED in the PROCESS OF THINKING
		if (!p->one_dead && !p->writing)
			write_message(p, num, p->msgs.thinking);
		if (p->one_dead && (pthread_mutex_lock(&p->forks[p->i]) || pthread_mutex_lock(&p->forks[(p->i + 1) % p->n_phi])))
			return (small_r(num));
		if (!p->one_dead && !p->writing)
			write_message(p, num, p->msgs.eating);
		count = 0;
		while (!p->one_dead && count < p->t_eat)
		{
			if (count >= p->t_die)
			{
				if (!p->writing)
					write_message(p, num, p->msgs.died);
				p->one_dead = 1;
				return (small_r(num));
			}
			usleep(9);
			count += 9;
		}
		pthread_mutex_unlock(&p->forks[p->i]);
		pthread_mutex_unlock(&p->forks[(p->i + 1) % p->n_phi]);
		if (!p->writing && !p->one_dead)
		{
			write_message(p, num, p->msgs.sleeping);
			count = 0;
			while (!p->one_dead && count < p->t_sleep)
			{
				if (count >= p->t_sleep)
				{
					if (!p->writing)
						write_message(p, num, p->msgs.died);
					p->one_dead = 1;
					return (small_r(num));
				}
				usleep(9);
				count += 9;
			}
			usleep(p->t_sleep);
		}
	}
	return (small_r(num));
}

void	start_threads(t_prog *p)
{
	gettimeofday(&(p->start_time), NULL);
	while (++p->i < p->n_phi)
		pthread_mutex_init(p->forks + p->i, 0);
	p->i = -1;
	p->one_dead = 0;
	while (++p->i < p->n_phi)
	{
		p->writing = 0;
		if (pthread_create(&(p->th[p->i]), NULL, &routine, p) != 0)
			perror("Failed to create thread\n");
		pthread_detach(p->th[p->i]);
		usleep(1);
	}
	// p->i = 0;
	// while (p->i < p->n_phi)
	// {
	// 	if (pthread_join(p->th[p->i], 0) != 0)
	// 		perror("Failed to join thread\n");
	// 	p->i++;
	// }
	p->i = -1;
	while (++p->i < p->n_phi)
		pthread_mutex_destroy(p->forks + p->i);
	pthread_exit(0);
}

int	main(int argc, char *argv[])
{
	t_prog p;
	t_msgs m;

	if (argc < 5 || argv[1][0] == 48 || argv[2][0] == 48)
	{
		ft_printf("Invalid number of arguments\n");
		return (0);
	}
	m.eating = " is eating\n";
	m.sleeping = " is sleeping\n";
	m.thinking = " is thinking\n";
	m.died = " died\n";
	p.msgs = m;
	p.argc = argc;
	p.argv = argv;
	build_params(&p);
	start_threads(&p);
	return (0);
}
