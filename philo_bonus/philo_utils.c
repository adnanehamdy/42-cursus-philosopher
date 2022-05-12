/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:28:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 09:09:26 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	supervisor(t_philo *philo)
{
	int	ms_time;

	philo->exit_status = 0;
	while (waitpid(0, &philo->exit_status, 0) != -1)
	{
		if (philo->exit_status)
		{
			ms_time = get_current_time() - philo->start_time;
			sem_wait(philo->msg);
			printf("%d ms %d died\n", ms_time, philo->index + 1);
			break ;
		}
	}
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!philo->is_finished[philo->index])
	{
		if ((get_current_time() - philo->last_eat[philo->index])
			>= philo->time_to_die
			&& !philo->is_eating[philo->index]
			&& !philo->is_finished[philo->index])
		{
			exit(1);
		}
	}
	return (NULL);
}

void	eating_proccess(t_philo *philo, sem_t *forks)
{
	pthread_t	is_dead;

	pthread_create(&is_dead, NULL, &routine, philo);
	sem_wait(forks);
	display("%d ms %d has taken the fork\n",
		philo, philo->index + 1, philo->msg);
	sem_wait(forks);
	display("%d ms %d has taken the fork\n",
		philo, philo->index + 1, philo->msg);
	philo->last_eat[philo->index] = get_current_time();
	philo->is_eating[philo->index] = 1;
	display("%d ms %d is eating\n", philo, philo->index + 1, philo->msg);
	ft_usleep(philo->time_to_eat);
	sem_post(forks);
	sem_post(forks);
}

void	create_proccesses(t_philo *philo, sem_t *forks)
{
	pid_t	pid;
	int		index;

	index = 0;
	while (index < philo->number_of_philo)
	{
		pid = fork_it();
		if (pid == 0)
			philosopher_life(philo, index, forks);
		index = index + 2;
	}
	index = 1;
	while (index < philo->number_of_philo)
	{
		pid = fork_it();
		if (pid == 0)
			philosopher_life(philo, index, forks);
		index = index + 2;
	}
}
