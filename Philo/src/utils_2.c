/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:50:31 by tide-pau          #+#    #+#             */
/*   Updated: 2026/03/02 16:33:34 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	timestamp(t_data *data)
{
	return (get_time_ms() - data->start_time);
}

void	death_sleep(long ms, t_data *data)
{
	long	start;

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
		usleep(100);
	}
}

int	monitor_cheack_death(t_data *data)
{
	pthread_mutex_lock(&data->mutex_death);
	if (data->death)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_death);
	return (0);
}

int	monitor_check_starving(t_data *data, long curr_time, int i)
{
	pthread_mutex_lock(&data->mutex_philo_meals);
	pthread_mutex_lock(&data->philos[i].mutex_lmt);
	if (!data->philos[i].finished && (curr_time
			- data->philos[i].last_meal_time) > data->time_die)
	{
		monitor_helper(data, i);
		pthread_mutex_unlock(&data->philos[i].mutex_lmt);
		pthread_mutex_unlock(&data->mutex_philo_meals);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].mutex_lmt);
	pthread_mutex_unlock(&data->mutex_philo_meals);
	return (0);
}
