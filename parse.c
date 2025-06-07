#include "philosopher.h"

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments\n"), 1);

	for (int i = 1; i < argc; i++)
	{
		if (!is_number(argv[i]))
			return (printf("Error: invalid argument '%s'\n", argv[i]), 1);
	}

	args->n_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->n_times_must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;

	if (args->n_philos <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (printf("Error: arguments must be positive integers\n"), 1);

	if (argc == 6 && args->n_times_must_eat <= 0)
		return (printf("Error: number of times each philosopher must eat must be > 0\n"), 1);

	return (0);
}
