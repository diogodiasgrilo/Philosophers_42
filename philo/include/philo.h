/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:25:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/08 18:48:20 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef	struct s_mesgs
{
	char	*eating;
	char	*sleeping;
	char	*thinking;
	char	*died;
}				t_msgs;

typedef struct s_philo
{
	int		id;
	int		last_meal;
}				t_philo;

typedef struct s_prog
{
	t_msgs			msgs;
	pthread_mutex_t	*forks;
	pthread_t		*th;
	t_philo			*philos;
	int				argc;
	char 			**argv;
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_m_eat;
	int				i;
	double			elapsed_time;
	int				one_dead;
	int				writing;
	struct			timeval start_time;
	struct			timeval current_time;
}				t_prog;

void	build_params(t_prog *p);
void	free_split(char *argv[]);
void	clear_and_exit(t_prog *p);

#endif