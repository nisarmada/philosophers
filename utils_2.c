/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 09:42:38 by nikos         #+#    #+#                 */
/*   Updated: 2024/09/04 14:53:23 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long   timestamp(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
    {
        perror("failed to get time");
        exit(EXIT_FAILURE);
    }
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long time_diff(long long start, long long end)
{
    return (end - start);
}

void exit_error(char *message)
{
    int i;

    i = 0;
    while (message[i])
        i++;
    write(2, "Error: ", 7);
    write(2, message, i);
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}
void ft_usleep(long long millisecs)
{
    long long  start;
    start = timestamp();
    while (timestamp() - start < millisecs)
        usleep(500);
}

void init_mutex(t_data *data)
{
    if (pthread_mutex_init(&data->num_meals_mutex, NULL) != 0)
        exit_error("failed to create num_meals mutex");
    if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
			exit_error("start mutex initialization failed");
    
}


