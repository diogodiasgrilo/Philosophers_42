/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:25:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:10 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

struct	s_prog;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				t_counter;
	int				dead;
	int				times_eaten;
	char			*num;
	char			*eating;
	char			*sleeping;
	char			*thinking;
	char			*died;
	int				n_phi;
	int				t_m_eat;
	pthread_t		th;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_prog	*p;
}				t_philo;

typedef struct s_prog
{
	int				i;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	char			**argv;
	int				begin;
	int				argc;
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_m_eat;
	pthread_mutex_t	writing;
	int				elapsed_time;
	struct timeval	start_time;
	struct timeval	current_time;
}				t_prog;

void	get_time(t_prog	*p);
int		find_death(t_prog *p);
void	*routine(void *philo_v);
void	*build_params(t_prog *p);
void	start_threads(t_prog *p);
void	*small_r(t_philo *philo);
void	free_split(char *argv[]);
void	*free_everything(t_prog *p);
void	*write_dead(t_philo *philo);
void	prep_philos(t_prog *p, int i);
int		arg_checker(int argc, char *argv[]);
void	mutex_manager(t_prog *p, int action);
void	write_message(t_philo *philo, char *msg, int eating);

#endif