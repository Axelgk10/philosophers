#include "philo.h"

static void	check_philosopher_status(t_data *data, int i, int *all_ate)
{
	pthread_mutex_lock(&data->meal_check);
	if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
	{
		print_status(&data->philos[i], "died");
		data->someone_died = 1;
	}
	else if (data->must_eat_count != -1
		&& data->philos[i].meals_eaten < data->must_eat_count)
		*all_ate = 0;
	pthread_mutex_unlock(&data->meal_check);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (!is_simulation_ended(data))
	{
		i = -1;
		all_ate = 1;
		while (++i < data->num_philos && !is_simulation_ended(data))
		{
			check_philosopher_status(data, i, &all_ate);
			usleep(100);
		}
		if (data->must_eat_count != -1 && all_ate && !is_simulation_ended(data))
		{
			pthread_mutex_lock(&data->meal_check);
			data->all_ate = 1;
			pthread_mutex_unlock(&data->meal_check);
			break ;
		}
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_philos)
		pthread_create(&data->philos[i].thread, NULL,
			philo_routine, &data->philos[i]);
	pthread_create(&monitor, NULL, monitor_routine, data);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_check);
	free(data->philos);
	free(data->forks);
}
