#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

// ------------------ STRUCTS ------------------
typedef struct s_data t_data;

typedef struct s_args
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_times_must_eat; // -1 si no se pasa
} t_args;


typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal;
	int			is_eating;
	pthread_t	thread;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	t_data		*data;
	t_args		*args;
} t_philo;


typedef struct s_data
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check_mutex;
	pthread_mutex_t	all_ate_mutex;
	int				someone_died;
	int				all_ate;
	t_philo			*philos;
	pthread_t		monitor_thread;
} t_data;


// ------------------ FUNCIONES PRINCIPALES ------------------

int		main(int argc, char **argv);
int		parse_args(int argc, char **argv, t_args *args);
int		init_data(t_data *data, t_args *args);
int		start_threads(t_data *data);

// ------------------ UTILIDADES ------------------

int			ft_atoi(const char *str);
int			is_number(char *str);
long		get_time_in_ms(void);
long long	get_time(void);
void		ft_usleep(long long time_in_ms);
void		print(t_philo *philo, char *msg);
void	free_data(t_data *data);

// ------------------ RUTINA ------------------

void		*routine(void *arg);
void		*monitor_philos(void *arg);

// ------------------ ACCIONES DEL FILÓSOFO ------------------

void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

#endif
