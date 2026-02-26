/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:08:41 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/26 16:55:06 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void monitor_helper(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_death);
	print_state(&data->philos[i], DIED);
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
		printf("\033[92mAll philos have finished eating\033[0m\n");
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
			if (philo_done(data))
				return (NULL);
			if (monitor_cheack_death(data))
				return (NULL);
			curr_time = get_time_ms();
			if (monitor_check_starving(data, curr_time, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
}
