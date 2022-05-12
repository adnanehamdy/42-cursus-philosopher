/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:58:41 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 07:47:30 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms_time)
{
	int	current_time;
	int	t;

	current_time = get_current_time();
	t = (ms_time * 9) / 10;
	usleep(t);
	while (get_current_time() - current_time < ms_time)
		usleep(250);
}

void	eating_proccess(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->mutex_fork[id]);
	display("%d ms %d has taken the fork\n", philo, id + 1);
	pthread_mutex_lock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
	display("%d ms %d has taken the fork\n", philo, id + 1);
	philo->last_eat[id] = get_current_time();
	philo->is_eating[id] = (bool)1;
	display("%d ms %d is eating\n", philo, id + 1);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_fork[id]);
	pthread_mutex_unlock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
	philo->is_eating[id] = (bool)0;
	if (philo->must_eat_ntimes != -1)
		philo->eat_time[id]++;
}

void	*routine(void *philosopher)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->mutex_id);
	id = philo->index;
	pthread_mutex_unlock(&philo->mutex_id);
	while (philo->must_eat_ntimes == -1 || !philo->all_has_eating_ntimes)
	{
		eating_proccess(philo, id);
		if (philo->all_has_eating_ntimes)
			return (NULL);
		display("%d ms %d is sleeping\n", philo, id + 1);
		ft_usleep(philo->time_to_sleep);
		display("%d ms %d is thinking\n", philo, id + 1);
	}
	return (NULL);
}

void	create_thread(t_philo	*philo)
{
	int	index;

	index = 0;
	philo->index = 0;
	while (index < philo->number_of_philo)
	{
		philo->index = index;
		pthread_create(&philo->t_philoype[index], NULL, &routine, philo);
		index = index + 2;
		usleep(50);
	}
	index = 1;
	while (index < philo->number_of_philo)
	{
		philo->index = index;
		pthread_create(&philo->t_philoype[index], NULL, &routine, philo);
		index = index + 2;
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (valid_arg(av, ac))
		return (1);
	philo = initialize_philo(av, ac);
	create_thread(philo);
	if (supervisor(philo))
		return (1);
	pthread_mutex_destroy(philo->mutex_fork);
	pthread_mutex_destroy(&philo->mutex_id);
	pthread_mutex_destroy(&philo->mutex_msg);
}
