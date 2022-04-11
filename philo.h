/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:48:18 by ahamdy            #+#    #+#             */
/*   Updated: 2022/04/11 17:05:06 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

/* philo data type*/
typedef struct philo
{
	pthread_t		*philo_type;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_id;
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*must_eat_ntimes;
	int				number_of_philo;
	int				*init_time;
} philo_t;

/* dependencies functions*/
int	ft_atoi(const char *str);
void	valid_arg(char ** av, int ac);

/* routine of the functions */
void	*routine(void *philosopher);
philo_t	*initialize_philo(char **av, int ac);