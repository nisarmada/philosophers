/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/31 13:24:50 by nikos         #+#    #+#                 */
/*   Updated: 2024/09/11 14:47:35 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_crew(t_data *data, int *array)
{
	int	i;

	i = 0;
	free(array);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->printf_mutex);
	free(data->forks);
	free(data->philo);
}

int	everyone_ate(t_data *data)
{
	int	all_fed;
	int	i;

	i = 0;
	all_fed = 1;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if (data->num_meals && data->philo[i].meals_eaten < data->num_meals)
		{
			all_fed = 0;
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
	return (all_fed);
}

void	handle_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->death_lock);
	if (!data->someone_died)
	{
		safe_printf(data, time_diff(data->start_time,
				timestamp()), data->philo[i].id, "died");
		data->someone_died = 1;
	}
	pthread_mutex_unlock(&data->death_lock);
}

int	check_death(t_data *data)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&data->death_lock);
	if (data->someone_died)
		flag = 1;
	pthread_mutex_unlock(&data->death_lock);
	return (flag);
}
