/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:01:13 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/12 09:10:37 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include<pthread.h>
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<sys/time.h>
# include<stdbool.h>
# include<semaphore.h>

typedef struct philo
{
	sem_t			*msg;
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*must_eat_ntimes;
	int				number_of_philo;
	int				*last_eat;
	int				start_time;
	bool			*is_eating;
	bool			*is_finished;
	int				exit_status;
}	t_philo;

void	*routine(void *philo);
int		fork_it(void);
int		valid_arg(char **av, int ac);
int		ft_atoi(const char *str);
int		get_current_time(void);
t_philo	*initialize_philo(char **av, int ac);
void	display(char *msg, t_philo *philo, int id, sem_t *sem_msg);
void	supervisor(t_philo *philo);
void	eating_proccess(t_philo *philo, sem_t *forks);
void	create_proccesses(t_philo *philo, sem_t *forks);
void	ft_usleep(int ms_time);
void	philosopher_life(t_philo *philo, int index, sem_t *forks);
#endif