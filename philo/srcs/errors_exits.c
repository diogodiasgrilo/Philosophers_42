/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:19:35 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/08 17:03:57 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_split(char *argv[])
{
	int i;

	i = -1;
	while (argv && argv[++i])
		free(argv[i]);
	free(argv);
}

void	clear_and_exit(t_prog *p)
{
	if (p->th)
		free(p->th);
	if (p->philos)
		free(p->philos);
	if (p->forks)
		free(p->forks);
	if (p->argv)
		free(p->argv);
	exit (0);
}