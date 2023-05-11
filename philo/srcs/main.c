/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:43:33 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/11 10:35:46 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int argc, char *argv[])
{
	t_prog	p;

	if (argc < 5 || argc > 6 || argv[1][0] == 48 || argv[2][0] == 48)
	{
		ft_printf("Invalid number of arguments\n");
		return (1);
	}
	p.argc = argc;
	p.argv = argv;
	if (!build_params(&p))
		return (2);
	start_threads(&p);
	return (0);
}
