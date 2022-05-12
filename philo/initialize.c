/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:49:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 07:43:08 by ahamdy           ###   ########.fr       */
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
	philo->t_philoype = (pthread_t *)
		malloc(sizeof(pthread_t) * number_of_philo);
	philo->mutex_fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * number_of_philo);
	philo->last_eat = (int *)malloc(sizeof(int) * number_of_philo);
	philo->is_eating = (bool *)malloc(sizeof(bool) * number_of_philo);
	philo->eat_time = (int *)malloc(sizeof(int) * number_of_philo);
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
		philo->must_eat_ntimes = ft_atoi(av[5]);
	}
	else
			philo->must_eat_ntimes = -1;
	index = 0;
	philo->all_has_eating_ntimes = 0;
	while (index < philo->number_of_philo)
	{
		philo->last_eat[index] = philo->start_time;
		philo->is_eating[index] = 0;
		philo->eat_time[index++] = 0;
	}
}

void	init_mutexes(t_philo *philo)
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

t_philo	*initialize_philo(char **av, int ac)
{
	t_philo	*philo;

	philo = allocate_elements_of_philo(av);
	initialize_time(av, philo, ac);
	init_mutexes(philo);
	return (philo);
}
