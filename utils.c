#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(long long time, t_data *data)
{
	long long	start;
	long long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time)
			break ;
		if (is_simulation_ended(data))
			break ;
		usleep(100);
	}
}

int	is_simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->meal_check);
	ended = data->someone_died || data->all_ate;
	pthread_mutex_unlock(&data->meal_check);
	return (ended);
}

void	print_status(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_died && !philo->data->all_ate)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
