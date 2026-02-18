/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:50:31 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/11 17:35:50 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/Philo.h"

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long timestamp(t_data *data)
{
    return (get_time_ms() - data->start_time);
}

void    death_sleep(long ms, t_data *data)
{
    long start;

    start = get_time_ms();
    while ((get_time_ms() - start) < ms)
    {
        pthread_mutex_lock(&data->mutex_death);
        if (data->death)
        {
            pthread_mutex_unlock(&data->mutex_death);
            break ;
        }
        pthread_mutex_unlock(&data->mutex_death);
        usleep (100);
    }
}
