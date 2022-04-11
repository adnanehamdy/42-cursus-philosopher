/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:20:19 by ahamdy            #+#    #+#             */
/*   Updated: 2022/04/08 17:32:34 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***check the number of arg and if they r valid ***/
void	valid_arg(char ** av, int ac)
{
	int	index;
	int index_y;

	index = 1;
	if (ac < 5 || ac > 6)
	{
		printf("error check the number of arguments\n");
		exit(1);
	}
	while (av[index])
	{
		index_y = 0;
		while (av[index][index_y])
		{
			if (av[index][index_y] < '0' || av[index][index_y] > '9')
			{
				printf("enter valid arguments\n");
				exit(1);
			}
			index_y++;
		}
		index++;
	}
}