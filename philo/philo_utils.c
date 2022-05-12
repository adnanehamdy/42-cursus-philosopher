/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:59:46 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 07:48:48 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_finished(t_philo	*philo)
{
	int	index;

	index = 0;
	while (index < philo->number_of_philo)
	{
		if (philo->must_eat_ntimes == -1
			|| philo->eat_time[index] < philo->must_eat_ntimes)
			return (1);
		index++;
	}
	philo->all_has_eating_ntimes = 1;
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
			&& !philo->is_eating[index])
		{
			pthread_mutex_lock(&philo->mutex_msg);
			printf("%d ms %d died\n",
				get_current_time() - philo->start_time, index + 1);
			return (1);
		}
		index = (index + 1) % philo->number_of_philo;
	}
	pthread_mutex_lock(&philo->mutex_msg);
	return (0);
}
