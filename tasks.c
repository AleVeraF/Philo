/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:37 by alvera-f          #+#    #+#             */
/*   Updated: 2025/06/07 16:46:39 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, const char *status)
{
	long	timestamp;

	timestamp = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	print_status(philo, "has taken a fork");

	pthread_mutex_lock(&philo->data->meal_check_mutex);
	philo->is_eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_check_mutex);

	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);

	philo->meals_eaten++;

	pthread_mutex_lock(&philo->data->meal_check_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->meal_check_mutex);

	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

int	check_philo_death(t_data *data, int i)
{
	long	now;

	pthread_mutex_lock(&data->meal_check_mutex);
	now = get_time();
	if ((now - data->philos[i].last_meal >= data->time_to_die))
	{
		data->someone_died = 1;
		pthread_mutex_unlock(&data->meal_check_mutex);
		pthread_mutex_lock(&data->print);
		printf("%lld %d died\n", now - data->start_time, data->philos[i].id);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_check_mutex);
	return (0);
}

int	check_all_philos_ate(t_data *data)
{
	if (data->must_eat > 0)
	{
		pthread_mutex_lock(&data->all_ate_mutex);
		if (data->all_ate >= data->n_philos)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(&data->all_ate_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->all_ate_mutex);
	}
	return (0);
}

void	*monitor_philos(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_philos_ate(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	print(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time;
	if (!philo->data->someone_died)
		printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_usleep(long long time_in_ms)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}


