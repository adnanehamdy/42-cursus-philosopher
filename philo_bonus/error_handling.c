/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:58:54 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 08:53:58 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_it(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("fork call failed\n");
		exit(1);
	}
	return (pid);
}

int	valid_arg(char **av, int ac)
{
	int	index;
	int	index_y;

	index = 1;
	if (ac < 5 || ac > 6)
	{
		printf("error check the number of arguments\n");
		return (1);
	}
	while (av[index])
	{
		index_y = 0;
		while (av[index][index_y])
		{
			if (av[index][index_y] < '0' || av[index][index_y] > '9')
			{
				printf("enter valid arguments\n");
				return (1);
			}
			index_y++;
		}
		index++;
	}
	return (0);
}
