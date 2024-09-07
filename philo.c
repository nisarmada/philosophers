/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 14:25:43 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/07 19:23:16 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_stuff(t_data *data, int *array, int ac)
{
	data->num_philo = array[0];
	data->time_to_die = array[1];
	data->time_to_eat = array[2];
	data->time_to_sleep = array[3];
	data->num_meals = 0;
	data->start_time = timestamp();
	if (data->start_time == -1)
		return (-1);
	data->someone_died = 0;
	data->num_meals = 0;
	data->philos_created = 0;
	if (ac == 6)
		data->num_meals = array[4];
	data->philo = malloc(data->num_philo * sizeof(t_philo));
	if (!data->philo)
		return (exit_error("philo malloc failed", 3));
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (exit_error("fork malloc failed", 3));
	init_mutex(data);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal = data->start_time;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (exit_error("fork initialization failed", 2));
		if (pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL) != 0)
			return (exit_error("failed to initialize last meal mutex", 2));
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
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!check_death(philo->data))
	{
		printf("%lld %i is thinking\n",
			time_diff(philo->data->start_time, timestamp()), philo->id);
		if (check_death(philo->data))
			return (NULL);
		if (philo->id % 2 == 0)
			even_philo(philo);
		else
			odd_philo(philo);
		if (check_death(philo->data) || philo->data->num_philo == 1)
			return (NULL);
		printf("%lld %i is sleeping\n",
			time_diff(philo->data->start_time, timestamp()), philo->id);
		ft_usleep(philo->data->time_to_sleep);
		if (philo->data->num_meals && everyone_ate(philo->data))
			return (NULL);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philo && !data->someone_died)
		{
			if ((data->num_meals && everyone_ate(data)) || data->someone_died)
				return (NULL);
			pthread_mutex_lock(&data->philo[i].last_meal_mutex);
			if ((timestamp() - data->philo[i].last_meal
					> (long long)data->time_to_die))
			{
				pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
				handle_death(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
		return (exit_error("failed at creating monitor thread", 1));
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id,
				NULL, philo_routine, &data->philo[i]) != 0)
			return (exit_error("failed to create philo thread", 1));
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (exit_error("failed to join thread", 1));
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (exit_error("failed to join monitor thread", 1));
	return (0);
}
