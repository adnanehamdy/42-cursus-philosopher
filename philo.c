/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:58:41 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/09 12:06:10 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms_time)
{
	int	current_time;

	current_time = get_current_time();
	while (get_current_time() - current_time < ms_time)
		usleep(300);
}

void	eating_proccess(t_philo *philo, int id)
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
}

void	*routine(void *philosopher)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->mutex_id);
	id = philo->index++;
	pthread_mutex_unlock(&philo->mutex_id);
	while (philo->must_eat_ntimes[id] == -1 || philo->must_eat_ntimes[id]--)
	{
		eating_proccess(philo, id);
		display("%d ms %d is sleeping\n", philo, id + 1);
		ft_usleep(philo->time_to_sleep);
		display("%d ms %d is thinking\n", philo, id + 1);
	}
	philo->is_finished[id] = 1;
	return (NULL);
}

int	main(int ac, char **av)
{
	int		index;
	t_philo	*philo;

	index = 0;
	if (valid_arg(av, ac))
		return (1);
	philo = initialize_philo(av, ac);
	philo->index = 0;
	while (index < philo->number_of_philo)
	{
		pthread_create(&philo->t_philoype[index++], NULL, &routine, philo);
		usleep(100);
	}
	if (supervisor(philo))
		return (1);
	pthread_mutex_destroy(philo->mutex_fork);
	pthread_mutex_destroy(&philo->mutex_id);
	pthread_mutex_destroy(&philo->mutex_msg);
}
