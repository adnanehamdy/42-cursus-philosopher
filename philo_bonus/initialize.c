/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:43:11 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 08:54:40 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
	struct timeval	tv;
	int				ms_time;

	gettimeofday(&tv, NULL);
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms_time);
}

t_philo	*allocate_elements_of_philo(char **av)
{
	int		number_of_philo;
	t_philo	*philo;

	number_of_philo = ft_atoi(av[1]);
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->must_eat_ntimes = (int *)malloc(sizeof(int) * number_of_philo);
	philo->last_eat = (int *)malloc(sizeof(int) * number_of_philo);
	philo->is_eating = (bool *)malloc(sizeof(bool) * number_of_philo);
	philo->is_finished = (bool *)malloc(sizeof(bool) * number_of_philo);
	philo->number_of_philo = number_of_philo;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->start_time = get_current_time();
	return (philo);
}

void	initialize_time(char **av, t_philo *philo, int ac)
{
	int	index;
	int	init_time;

	index = 0;
	init_time = philo->start_time;
	if (ac == 6)
	{
		philo->must_eat_ntimes[index++] = ft_atoi(av[5]);
		while (index < philo->number_of_philo)
			philo->must_eat_ntimes[index++] = philo->must_eat_ntimes[0];
	}
	else
	{
		while (index < philo->number_of_philo)
			philo->must_eat_ntimes[index++] = -1;
	}
	index = 0;
	while (index < philo->number_of_philo)
	{
		philo->last_eat[index] = philo->start_time;
		philo->is_eating[index] = 0;
		philo->is_finished[index++] = 0;
	}
}

t_philo	*initialize_philo(char **av, int ac)
{
	t_philo	*philo;
	int		index;

	index = 0;
	philo = allocate_elements_of_philo(av);
	initialize_time(av, philo, ac);
	while (index < philo->number_of_philo)
	{
		philo->last_eat[index] = philo->start_time;
		index++;
	}
	return (philo);
}
