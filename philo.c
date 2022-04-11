#include "philo.h"

static void display(char *msg, philo_t *philo, int id)
{
	pthread_mutex_lock(&philo->mutex_msg);
	printf(msg, id);
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
		display("this philo %d took the fork\n", philo, id + 1);
		pthread_mutex_lock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
		display("this philo %d took the fork\n", philo, id + 1);
		display("this philo %d is eating\n", philo, id + 1);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex_fork[id]);
		pthread_mutex_unlock(&philo->mutex_fork[(id + 1) % philo->number_of_philo]);
		display("the philo %d is sleeping\n", philo, id + 1);
		usleep(philo->time_to_sleep * 1000);
		display("the philo %d is thinking\n", philo, id + 1);
	}
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
		pthread_create(&philo->philo_type[index++], NULL, &routine,  philo);
		usleep(100);
	}
	index = 0;
	while (index < philo->number_of_philo)
		pthread_join(philo->philo_type[index++], NULL);
	pthread_mutex_destroy(philo->mutex_fork);
	pthread_mutex_destroy(&philo->mutex_id);
	pthread_mutex_destroy(&philo->mutex_msg);
}