/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 14:25:36 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/11 14:46:40 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct philo_s	t_philo;
typedef struct data_s	t_data;

typedef struct data_s
{
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				num_meals;
	int				num_philo;
	long long		start_time;
	bool			someone_died;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	num_meals_mutex;
	pthread_t		monitor_thread;
	int				philos_created;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	printf_mutex;
}	t_data;

typedef struct philo_s
{
	t_data			*data;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread_id;
	int				id;
	long long		last_meal;
	int				meals_eaten;
}	t_philo;

int			is_digit(char c);
int			input_check(char *av);
void		print_array(int *array);
int			init_stuff(t_data *data, int *array, int ac);
int			*turn_to_int(char **av);
int			ft_atoi(const char *nptr);
int			init_philos(t_data *data);
int			create_threads(t_data *data);
long long	timestamp(void);
long long	time_diff(long long start, long long end);
int			exit_error(char *message, int error_code);
void		*monitor_routine(void *arg);
void		ft_usleep(long long millisecs);
int			everyone_ate(t_data *data);
int			init_mutex(t_data *data);
void		cleanup_crew(t_data *data, int *array);
int			pickup_forks(t_philo *philo, pthread_mutex_t *first,
				pthread_mutex_t *second, t_data *data);
void		putdown_forks(pthread_mutex_t *first, pthread_mutex_t *second);
void		eat(t_philo *philo, t_data *data);
void		even_philo(t_philo *philo);
void		odd_philo(t_philo *philo);
void		handle_death(t_data *data, int i);
int			check_death(t_data *data);
int			safe_check(t_data *data);
void		safe_printf(t_data *data, long long a, int i, char *str);
#endif