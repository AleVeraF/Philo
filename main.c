/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:00 by alvera-f          #+#    #+#             */
/*   Updated: 2025/06/07 18:15:10 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	return (0);
}

int	start_simulation(t_args *args)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (init_data(&data, args))
	{
		free_data(&data);
		return (1);
	}
	if (start_threads(&data))
	{
		free_data(&data);
		return (1);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_philos, &data) != 0)
	{
		printf("Error: pthread_create (monitor)\n");
		free_data(&data);
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_threads(&data);
	free_data(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (parse_args(argc, argv, &args))
		return (1);
	return (start_simulation(&args));
}
