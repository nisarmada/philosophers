/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 14:25:36 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/08/31 13:45:38 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#define PHILO_H
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct philo_s philo_t;
typedef struct data_s data_t;

typedef struct data_s{
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	philo_t			*philo;
	pthread_mutex_t	*forks;
	int				num_meals;
	int				num_philo;
	long long		start_time;
	bool			someone_died;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	num_meals_mutex;
	pthread_t		monitor_thread;
} data_t;

typedef struct philo_s{
	data_t			*data;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread_id;
	int				id;
	long long		last_meal;
	int				meals_eaten;
} philo_t;

int			is_digit(char c);
int			input_check(char *av);
void		print_array(int *array);
void		init_stuff(data_t *data, int *array, int ac);
int			*turn_to_int(char **av);
int			ft_atoi(const char *nptr);
void		init_philos(data_t *data);
void		create_threads(data_t *data);
long long	timestamp(void);
long long	time_diff(long long start, long long end);
void		exit_error(char *message);
void		*monitor_routine(void *arg);
void		ft_usleep(long long millisecs);
int			everyone_ate(data_t *data);
void		init_mutex(data_t *data);
void		cleanup_crew(data_t *data, int *array);

#endif