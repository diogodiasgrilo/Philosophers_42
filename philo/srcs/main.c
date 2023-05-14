/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:43:33 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/14 17:02:59 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int argc, char *argv[])
{
	t_prog	p;

	if (arg_checker(argc, argv))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	p.argc = argc;
	p.argv = argv;
	if (!build_params(&p))
		return (1);
	start_threads(&p);
	free_everything(&p);
	return (0);
}
