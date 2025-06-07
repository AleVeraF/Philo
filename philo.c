#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->meal_check_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->meal_check_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_check_mutex);

		philo_think(philo);
		philo_eat(philo);

		if (philo->args->n_times_must_eat > 0 && philo->meals_eaten >= philo->args->n_times_must_eat)
		{
			pthread_mutex_lock(&philo->data->all_ate_mutex);
			philo->data->all_ate++;
			pthread_mutex_unlock(&philo->data->all_ate_mutex);
			break;
		}
		philo_sleep(philo);
	}
	return (NULL);
}


int	start_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_in_ms();
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->threads[i], NULL, routine, &data->philos[i]) != 0)
			return (printf("Error: creating thread for philo %d\n", i + 1), 1);
		i++;
	}
	return (0);
}



long get_time_in_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000); // Convertir a milisegundos
}


int	init_data(t_data *data, t_args *args)
{
	int	i;

	data->n_philos = args->n_philos;
	data->time_to_die = args->time_to_die;
	data->time_to_eat = args->time_to_eat;
	data->time_to_sleep = args->time_to_sleep;
	data->must_eat = args->n_times_must_eat;
	data->start_time = 0;
	data->someone_died = 0;
	data->all_ate = 0;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->forks || !data->philos || !data->threads)
		return (printf("Error: malloc\n"), 1);

	if (pthread_mutex_init(&data->print, NULL) != 0
		|| pthread_mutex_init(&data->meal_check_mutex, NULL) != 0
		|| pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
		return (printf("Error: init mutex\n"), 1);

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: init fork mutex\n"), 1);
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].args = args;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->n_philos];
		i++;
	}
	return (0);
}


void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_check_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);

	free(data->forks);
	free(data->philos);
	free(data->threads);
}








