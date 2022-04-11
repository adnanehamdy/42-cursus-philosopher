/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:49:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/04/11 17:15:51 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
	struct timeval tv;
	int	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	allocate_elements_of_philo(char **av, philo_t *philo)
{
	int	number_of_philo;
	number_of_philo = ft_atoi(av[1]);
	philo = (philo_t *)malloc(sizeof(philo_t));
	philo->philo_type = (pthread_t *)malloc(sizeof(pthread_t) * number_of_philo);
	philo->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number_of_philo);
	philo->must_eat_ntimes = (int *)malloc(sizeof(int) * number_of_philo);
	philo->init_time = (int *)malloc(sizeof(int) * number_of_philo);
	philo->number_of_philo = number_of_philo;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);	
}

void	initialize_time(char **av, philo_t *philo, int ac)
{
	int	index;
	int	init_time;

	index = 0;
	init_time = get_current_time();
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
		philo->init_time[index++] = init_time;
}

void	init_mutexes(char **av, philo_t)
{
	int	index;

	index = 0;
	while (index < philo->number_of_philo)
	{
		pthread_mutex_init(&philo->mutex_fork[index], NULL);
		index++;
	}
	pthread_mutex_init(&philo->mutex_id, NULL);
	pthread_mutex_init(&philo->mutex_msg, NULL);
}

philo_t	*initialize_philo(char **av, int ac)
{
	philo_t	*philo;

	index = 0;
	allocate_elements_of_philo(av, philo);
	initialize_time(av, philo, ac);
	init_mutexes(av, philo);
	index = 0;

	return (philo);
}