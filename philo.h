/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 14:25:36 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/04 14:51:56 by nikos         ########   odam.nl         */
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

typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_data{
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
} t_data;

typedef struct s_philo{
	t_data			*data;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread_id;
	int				id;
	long long		last_meal;
	int				meals_eaten;
} t_philo;

int			is_digit(char c);
int			input_check(char *av);
void		print_array(int *array);
void		init_stuff(t_data *data, int *array, int ac);
int			*turn_to_int(char **av);
int			ft_atoi(const char *nptr);
void		init_philos(t_data *data);
void		create_threads(t_data *data);
long long	timestamp(void);
long long	time_diff(long long start, long long end);
void		exit_error(char *message);
void		*monitor_routine(void *arg);
void		ft_usleep(long long millisecs);
int			everyone_ate(t_data *data);
void		init_mutex(t_data *data);
void		cleanup_crew(t_data *data, int *array);
void		pre_philo_routine(t_philo *philo);
void 		philo_eating(t_philo *philo);
#endif