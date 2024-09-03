/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/31 13:24:50 by nikos         #+#    #+#                 */
/*   Updated: 2024/09/03 18:28:43 by nikos         ########   odam.nl         */
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

void pre_philo_routine(philo_t *philo)
{
    while (1)
    {
        pthread_mutex_lock(&philo->data->start_mutex);
        if (philo->data->philos_created)
        {
            pthread_mutex_unlock(&philo->data->start_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->start_mutex);
        usleep(100);
    }
}