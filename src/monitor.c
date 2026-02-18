/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:08:41 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/18 14:09:45 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/Philo.h"

void    monitor_helper(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_death);
    print_state(&data->philos[i], "died");
    data->death = 1;
    pthread_mutex_unlock(&data->mutex_death);
}

void    *monitor(void *arg)
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
            if ((curr_time - data->philos[i].last_meal_time) > data->time_die)
                return (monitor_helper(data, i),printf("TEST\n"), NULL);
            i++;
        }
        usleep(100);
    }
}
