/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 13:39:12 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/11 14:26:25 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_check(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

void	safe_printf(t_data *data, long long a, int i, char *str)
{
	pthread_mutex_lock(&data->printf_mutex);
	printf("%lld %i %s\n", a, i, str);
	pthread_mutex_unlock(&data->printf_mutex);
}
