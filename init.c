#include "philo.h"

static int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_check_digit(argv[i]))
		{
			printf("Error: Invalid arguments\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (!ft_check_input(argc, argv))
		return (1);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat_count <= 0))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
		return (1);
	data->someone_died = 0;
	data->all_ate = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
	}
	return (0);
}
