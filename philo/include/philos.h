/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:25:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/15 18:53:16 by diogpere         ###   ########.fr       */
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

struct	s_prog;

typedef struct s_fork
{
	pthread_mutex_t	*fork;
	int				state;
}				t_fork;

typedef struct s_philo
{
	char			*num;
	char			*eating;
	char			*sleeping;
	char			*thinking;
	char			*died;
	int				id;
	int				dead;
	int				n_phi;
	int				t_m_eat;
	int				last_meal;
	pthread_t		th;
	struct s_prog	*p;
	pthread_mutex_t	*writing;
	t_fork			*l_fork;
	t_fork			*r_fork;
}				t_philo;

typedef struct s_prog
{
	t_philo			**philos;
	char			**argv;
	int				i;
	int				argc;
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_m_eat;
	int				t_all_eaten;
	t_fork			**states;
	pthread_mutex_t	**forks;
	pthread_mutex_t	writing;
	struct timeval	start_time;
	struct timeval	current_time;
}				t_prog;

char				*ft_itoa(int n);
int					ft_isdigit(int c);
int					get_time(t_prog	*p);
int					find_death(t_prog *p);
void				*unlock(t_philo *philo);
void				*routine(void *philo_v);
int					ft_strlen(const char *s);
int					ft_atoi(const char *str);
void				*build_params(t_prog *p);
void				start_threads(t_prog *p);
void				free_split(char *argv[]);
void				*free_everything(t_prog *p);
int					write_dead(t_philo *philo);
void				prep_philos(t_prog *p, int i);
int					arg_checker(int argc, char *argv[]);
void				mutex_manager(t_prog *p, int action);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strlcat(char *dst, const char *src, int dstsize);
int					write_message(t_philo *philo, char *msg, int eating);
unsigned long int	ft_strlcpy(char *dst, const char *src, \
		unsigned long int dstsize);

#endif