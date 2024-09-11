/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/05 17:38:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/11 14:47:19 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_forks(t_philo *philo, pthread_mutex_t *first,
	pthread_mutex_t *second, t_data *data)
{
	pthread_mutex_lock(first);
	if (check_death(data))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	safe_printf(data, time_diff(philo->data->start_time,
			timestamp()), philo->id, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_unlock(first);
		return (3);
	}
	pthread_mutex_lock(second);
	if (check_death(data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (2);
	}
	safe_printf(data, time_diff(philo->data->start_time, timestamp()),
		philo->id, "has taken a fork");
	return (0);
}

void	putdown_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	eat(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return ;
	safe_printf(data, time_diff(philo->data->start_time, timestamp()),
		philo->id, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = timestamp();
	if (philo->last_meal == -1)
		return ;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (check_death(data))
		return ;
	ft_usleep(philo->data->time_to_eat);
}

void	even_philo(t_philo *philo)
{
	if (pickup_forks(philo, philo->left, philo->right, philo->data) != 0)
		return ;
	eat(philo, philo->data);
	putdown_forks(philo->left, philo->right);
}

void	odd_philo(t_philo *philo)
{
	if (pickup_forks(philo, philo->right, philo->left, philo->data) != 0)
		return ;
	eat(philo, philo->data);
	putdown_forks(philo->right, philo->left);
}
