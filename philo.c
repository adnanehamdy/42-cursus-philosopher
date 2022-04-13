/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:58:41 by ahamdy            #+#    #+#             */
/*   Updated: 2022/04/13 16:57:37 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_all_finished(philo_t	*philo)
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

void	ft_usleep(int ms_time)
{
	int	current_time;

	current_time = get_current_time();
	while (get_current_time() - current_time < ms_time)
		usleep(300);
}
void	display(char *msg, philo_t *philo, int id)
{
	int ms_time;

	ms_time = get_current_time() - philo->start_time;
	pthread_mutex_lock(&philo->mutex_msg);
	printf(msg,ms_time, id);
	pthread_mutex_unlock(&philo->mutex_msg);
}

void	*routine(void *philosopher)
{
	philo_t	*philo;
	int id;

	philo = (philo_t *)philosopher;
	pthread_mutex_lock(&philo->mutex_id);
	id = philo->index++;
	pthread_mutex_unlock(&philo->mutex_id);
	while (philo->must_eat_ntimes[id] == -1 || philo->must_eat_ntimes[id]--)
	{
		pthread_mutex_lock(&philo->mutex_fork[id]);
		display("%d ms %d has taken the fork\n", philo, id + 1);
		pthread_mutex_lock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
		display("%d ms %d has taken the fork\n", philo, id + 1);
		display("%d ms %d is eating\n", philo, id + 1);
		philo->last_eat[id] = get_current_time();
		philo->is_eating[id] = (bool)1;
		ft_usleep(philo->time_to_eat);
		philo->is_eating[id] = (bool)0;
		pthread_mutex_unlock(&philo->mutex_fork[id]);
		display("%d ms %d put the fork\n", philo, id + 1);
		pthread_mutex_unlock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
		display("%d ms %d put the fork\n", philo, id + 1);
		display("%d ms %d is sleeping\n", philo, id + 1);
		ft_usleep(philo->time_to_sleep);
		display("%d ms %d is thinking\n", philo, id + 1);
	}
	philo->is_finished[id] = 1;
	return (NULL);
}

int main(int ac, char **av)
{
	int	index;
	philo_t *philo;

	index = 0;
	valid_arg(av, ac);
	philo = initialize_philo(av, ac);
	philo->index = 0; 
	while (index < philo->number_of_philo)
	{
		pthread_create(&philo->philo_type[index++], NULL, &routine, philo);
		usleep(100);
	}
	index = 0;
	while(is_all_finished(philo))
	{
		if ((get_current_time() - philo->last_eat[index]) >= philo->time_to_die
			&& !philo->is_eating[index] && !philo->is_finished[index])
		{
			display("%d ms %d died",philo, index + 1);
			return (0);
		}
		index = (index + 1) % philo->number_of_philo;
	}
	index = 0;	
	while (index < philo->number_of_philo)
		pthread_join(philo->philo_type[index++], NULL);
	pthread_mutex_destroy(philo->mutex_fork);
	pthread_mutex_destroy(&philo->mutex_id);
	pthread_mutex_destroy(&philo->mutex_msg);
}