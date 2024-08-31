/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 09:42:38 by nikos         #+#    #+#                 */
/*   Updated: 2024/08/31 13:58:56 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timestamp(void)
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

void init_mutex(data_t *data)
{
    if (pthread_mutex_init(&data->num_meals_mutex, NULL) != 0)
        exit_error("failed to create num_meals mutex");
}

int everyone_ate(data_t *data)
{
   int   all_fed;
    int   i;

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
    if (all_fed)
    {
        pthread_mutex_lock(&data->num_meals_mutex);
        printf("each philo ate %i meals\n", data->num_meals);
        pthread_mutex_unlock(&data->num_meals_mutex);
    }
    return (all_fed);
}
