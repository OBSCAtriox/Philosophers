/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:08:41 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/23 18:57:40 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void monitor_helper(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_death);
    print_state(&data->philos[i], "died");
    data->death = 1;
    pthread_mutex_unlock(&data->mutex_death);
}

int philo_done(t_data *data)
{
    pthread_mutex_lock(&data->mutex_philo_meals);
    if (data->num_meals > 0 && data->philo_done == data->num_phi)
    {
        pthread_mutex_unlock(&data->mutex_philo_meals);
        pthread_mutex_lock(&data->mutex_print);
        printf("\033[92mAll philos have finished eating\n");
        pthread_mutex_unlock(&data->mutex_print);
        return (1);
    }
    pthread_mutex_unlock(&data->mutex_philo_meals);
    return (0);
}

void *monitor(void *arg)
{
    t_data *data;
    int i;
    long curr_time;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->num_phi)
        {
            pthread_mutex_lock(&data->mutex_death);
            if (data->death)
            {
                pthread_mutex_unlock(&data->mutex_death);
                return NULL;
            }
            pthread_mutex_unlock(&data->mutex_death);
            curr_time = get_time_ms();
            pthread_mutex_lock(&data->philos[i].mutex_lmt);
            if ((curr_time - data->philos[i].last_meal_time) > data->time_die)
            {
                monitor_helper(data, i);
                pthread_mutex_unlock(&data->philos[i].mutex_lmt);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philos[i].mutex_lmt);
            if (philo_done(data))
                return (NULL);
            i++;
        }
        usleep(100);
    }
}
