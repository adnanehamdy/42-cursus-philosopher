/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:46 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/10 11:27:52 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_finished(t_philo	*philo)
{
	int	index;

	index = 0;
	while (index < philo->number_of_philo)
	{
		if (!philo->is_finished[index])
			return (1);
		index++;
	}
	return (0);
}

void	display(char *msg, t_philo *philo, int id)
{
	int	ms_time;

	pthread_mutex_lock(&philo->mutex_msg);
	ms_time = get_current_time() - philo->start_time;
	printf(msg, ms_time, id);
	pthread_mutex_unlock(&philo->mutex_msg);
}

int	supervisor(t_philo *philo)
{
	int	index;

	index = 0;
	while (is_all_finished(philo))
	{
		if ((get_current_time() - philo->last_eat[index]) >= philo->time_to_die
			&& !philo->is_eating[index] && !philo->is_finished[index])
		{
/* 			display("%d ms %d died", philo, index + 1); */
            	//ms_time = get_current_time() - philo->start_time;
			pthread_mutex_lock(&philo->mutex_msg);
			printf("%d ms %d died\n", get_current_time() - philo->start_time, index + 1);	
			return (1);
		}
		index = (index + 1) % philo->number_of_philo;
	}
	return (0);
}
