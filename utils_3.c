/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/31 13:24:50 by nikos         #+#    #+#                 */
/*   Updated: 2024/09/04 15:03:08 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    cleanup_crew(t_data *data, int *array)
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
    pthread_mutex_destroy(&data->num_meals_mutex);
    free(data->forks);
    free(data->philo);
}

void pre_philo_routine(t_philo *philo)
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

int everyone_ate(t_data *data)
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
