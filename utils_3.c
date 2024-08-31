/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/31 13:24:50 by nikos         #+#    #+#                 */
/*   Updated: 2024/08/31 13:41:10 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_crew(data_t *data, int *array)
{
    int i;

    i = 0;
    free(array);
    while (i < data->num_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
        i++;
    }
    pthread_mutex_destroy(&data->death_lock);
    free(data->forks);
    free(data->philo);
}