#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_args		args;
	t_data		data;
	pthread_t	monitor_thread;

	// Inicialización de datos
	if (parse_args(argc, argv, &args))
		return (1);
	if (init_data(&data, &args))
	{
		free_data(&data);
		return (1);
	}

	// Crear hilos de filósofos
	if (start_threads(&data))
	{
		free_data(&data);
		return (1);
	}

	// Crear hilo de monitoreo
	if (pthread_create(&monitor_thread, NULL, monitor_philos, &data) != 0)
	{
		printf("Error: pthread_create (monitor)\n");
		free_data(&data);
		return (1);
	}

	// Esperar a que los hilos terminen
	pthread_join(monitor_thread, NULL);

	for (int i = 0; i < data.n_philos; i++)
		pthread_join(data.threads[i], NULL);

	// Limpieza de recursos
	free_data(&data);
	return (0);
}
