int	parse_args(int argc, char **argv, t_data *data)
{
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->must_eat_count = -1;

    if (argc == 6)
        data->must_eat_count = atoi(argv[5]);
    if (data->num_philos <= 0 || data->time_to_die <= 0 || 
		data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
		(argc == 6 && data->must_eat_count <= 0))
    {
        pritnf("Error: Invalid arguments\n");
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
