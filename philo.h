#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	int				all_ate;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
}	t_data;

// Functions
int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
long long	get_time(void);
void		smart_sleep(long long time, t_data *data);
void		print_status(t_philo *philo, char *str);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			start_simulation(t_data *data);
void		cleanup(t_data *data);

#endif
