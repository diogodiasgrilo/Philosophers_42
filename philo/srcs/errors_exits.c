/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:19:35 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/12 16:56:45 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

void	free_split(char *argv[])
{
	int	i;

	i = -1;
	while (argv && argv[++i])
		free(argv[i]);
	free(argv);
}

void	free_struct(t_philo *philo)
{
	free(philo->num);
	free(philo->eating);
	free(philo->sleeping);
	free(philo->thinking);
	free(philo->died);
}

void	*free_everything(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phi)
	{
		free_struct(p->philos[i]);
		free(p->philos[i]);
		free(p->forks[i]);
	}
	free(p->philos);
	free(p->forks);
	return (0);
}

int	arg_checker(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}
