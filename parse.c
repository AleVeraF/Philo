/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:12 by alvera-f          #+#    #+#             */
/*   Updated: 2025/06/07 17:15:33 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parse_args(int argc, char **argv, t_args *args)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments\n"), 1);
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (printf("Error: invalid argument '%s'\n", argv[i]), 1);
		i++;
	}
	args->n_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->n_times_must_eat = ft_atoi(argv[5]);
	else
		args->n_times_must_eat = -1;
	if (args->n_philos <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (printf("Error: arguments must be positive integers\n"), 1);
	if (argc == 6 && args->n_times_must_eat <= 0)
		return (printf("Error\n"), 1);
	return (0);
}
