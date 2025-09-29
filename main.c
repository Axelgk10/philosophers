int main(argc int, argv **char)
{
    t_data  data;

    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
    }
    if (parse_args(argc, argv, &data) != 0)
		return (1);
	
	if (init_data(&data) != 0)
		return (1);
	
	if (start_simulation(&data) != 0)
		return (1);
	
	cleanup(&data);
	return (0);
}
