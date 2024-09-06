/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 09:42:38 by nikos         #+#    #+#                 */
/*   Updated: 2024/09/06 15:31:21 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (exit_error("failed to get time", -1));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long start, long long end)
{
	return (end - start);
}

int	exit_error(char *message, int error_code)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(2, "Error: ", 7);
	write(2, message, i);
	write(2, "\n", 1);
	return (error_code);
}

void	ft_usleep(long long millisecs)
{
	long long	start;

	start = timestamp();
	if (start == -1)
		return ;
	while (timestamp() - start < millisecs)
		usleep(500);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->num_meals_mutex, NULL) != 0)
		return (exit_error("failed to create num_meals mutex", 4));
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
		return (exit_error("start mutex initialization failed", 4));
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (exit_error("death mutex failed", 4));
	return (0);
}
