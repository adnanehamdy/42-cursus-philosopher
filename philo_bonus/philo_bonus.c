/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:55:11 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 09:07:51 by ahamdy           ###   ########.fr       */
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

void	ft_usleep(int ms_time)
{
	int	current_time;

	current_time = get_current_time();
	while (get_current_time() - current_time < ms_time)
		usleep(100);
}

void	display(char *msg, t_philo *philo, int id, sem_t *sem_msg)
{
	int	ms_time;

	ms_time = get_current_time() - philo->start_time;
	sem_wait(sem_msg);
	printf(msg, ms_time, id);
	sem_post(sem_msg);
}

void	philosopher_life(t_philo *philo, int index, sem_t *forks)
{
	philo->index = index;
	while (philo->must_eat_ntimes[index] == -1
		|| philo->must_eat_ntimes[index]--)
	{
		eating_proccess(philo, forks);
		philo->is_eating[index] = 0;
		display("%d ms %d is sleeping\n", philo, index + 1, philo->msg);
		ft_usleep(philo->time_to_sleep);
		display("%d ms %d is thinking\n", philo, index + 1, philo->msg);
	}
	philo->is_finished[index] = 1;
	sem_close(forks);
	sem_close(philo->msg);
	exit(0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	sem_t	*forks;

	if (valid_arg(av, ac))
		return (1);
	philo = initialize_philo(av, ac);
	sem_unlink("forks");
	sem_unlink("msg");
	forks = sem_open("forks", O_CREAT, 0664, philo->number_of_philo);
	philo->msg = sem_open("msg", O_CREAT, 0664, 1);
	create_proccesses(philo, forks);
	supervisor(philo);
	sem_close(forks);
	sem_close(philo->msg);
}
