#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		while (!is_simulation_ended(philo->data))
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_check);
	print_status(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		smart_sleep(10, philo->data);
	while (!is_simulation_ended(philo->data))
	{
		eat(philo);
		if (is_simulation_ended(philo->data))
			break ;
		print_status(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
		if (is_simulation_ended(philo->data))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}
