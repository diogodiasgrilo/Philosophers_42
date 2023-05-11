/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:19:35 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/11 10:35:53 by diogpere         ###   ########.fr       */
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

int	clear_and_exit(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phi)
	{
		free(p->philos[i].num);
		free(p->philos[i].eating);
		free(p->philos[i].sleeping);
		free(p->philos[i].thinking);
		free(p->philos[i].died);
	}
	if (p->philos)
		free(p->philos);
	if (p->forks)
		free(p->forks);
	if (p->argv)
		free_split(p->argv);
	return (0);
}
