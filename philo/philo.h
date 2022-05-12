/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:48:18 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/10 15:51:36 by ahamdy           ###   ########.fr       */
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

/* philo data type*/
typedef struct philo
{
	pthread_t		*t_philoype;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_id;
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_ntimes;
	int				number_of_philo;
	int				*last_eat;
	int				start_time;
	bool			*is_eating;
	int				*eat_time;
	bool			all_has_eating_ntimes;
}	t_philo;

/* dependencies functions*/
int		ft_atoi(const char *str);
int		valid_arg(char **av, int ac);

/* routine of the functions */
void	*routine(void *philosopher);
t_philo	*initialize_philo(char **av, int ac);
int		get_current_time(void);
int		supervisor(t_philo *philo);
void	display(char *msg, t_philo *philo, int id);
#endif