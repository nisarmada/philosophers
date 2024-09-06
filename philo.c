/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 14:25:43 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/04 14:56:05 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_stuff(t_data *data, int *array, int ac)
{
	data->num_philo = array[0];
	data->time_to_die = array[1];
	data->time_to_eat = array[2];
	data->time_to_sleep = array[3];
	data->num_meals = 0;
	data->start_time = timestamp();
	data->someone_died = 0;
	data->num_meals = 0;
	data->philos_created = 0;
	if (ac == 6)
		data->num_meals = array[4];
	data->philo = malloc(data->num_philo * sizeof(t_philo));
	if (!data->philo)
		exit_error("philo malloc failed");
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		exit_error("fork malloc failed");
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		exit_error("death mutex failed");
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal = data->start_time;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			exit_error("fork initialization failed");
		if (pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL) != 0)
			exit_error("failed to initialize last meal mutex");
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].left = &data->forks[i];
		data->philo[i].right = &data->forks[(i + 1) % data->num_philo];
		data->philo[i].last_meal = data->start_time;
		i++;
	}
}
void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	// if (philo->id % 2 != 0)
	// 	ft_usleep(philo->data->time_to_eat / 2);
	while (1)
	{
		printf("%lld %i is thinking\n",  time_diff(philo->data->start_time, timestamp()), philo->id);
		pthread_mutex_lock(philo->left);
		printf("%lld %i picked left fork\n",  time_diff(philo->data->start_time, timestamp()), philo->id);
		pthread_mutex_lock(philo->right);
		printf("%lld %i picked right fork\n",  time_diff(philo->data->start_time, timestamp()), philo->id);
		printf("%lld %i is eating\n",  time_diff(philo->data->start_time, timestamp()), philo->id);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = timestamp();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%lld %i is sleeping\n", time_diff(philo->data->start_time, timestamp()), philo->id);
		ft_usleep(philo->data->time_to_sleep);
		if (philo->data->num_meals && everyone_ate(philo->data))
			exit(EXIT_SUCCESS);
	}
	return (NULL);
}
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->philo[i].last_meal_mutex);
			if ((timestamp() - data->philo[i].last_meal > (long long)data->time_to_die))
			{ 
				pthread_mutex_lock(&data->death_lock);
				printf("%lld %i died\n", time_diff(data->start_time, timestamp()), data->philo[i].id);
				data->someone_died  = 1;
				pthread_mutex_unlock(&data->death_lock);
				pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
				exit(EXIT_SUCCESS);
			}
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
		exit_error("failed at creating monitor thread");
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL,
				philo_routine, &data->philo[i]) != 0)
			exit_error("failed to create philo thread");
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			exit_error("failed to join thread");
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		exit_error("failed to join monitor thread");
}
