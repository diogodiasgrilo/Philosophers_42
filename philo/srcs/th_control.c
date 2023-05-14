/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:32:53 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/14 17:07:05 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	get_time(t_prog *p)
{
	struct timeval	current_time;
	long			seconds;
	long			microseconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - p->start_time.tv_sec;
	microseconds = current_time.tv_usec - p->start_time.tv_usec;
	return ((seconds * 1000) + (microseconds / 1000));
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
			printf("Failed to create thread!\n");
	i = -1;
	while (++i < p->n_phi)
		if (pthread_join(p->philos[i]->th, 0))
			printf("Failed to join thread!\n");
	mutex_manager(p, 0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		t_length;

	t_length = 0;
	t_length += ft_strlen(s1);
	t_length += ft_strlen(s2);
	new_str = (char *)malloc((sizeof(char) * t_length + 1));
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, s2, t_length + 1);
	return (new_str);
}
