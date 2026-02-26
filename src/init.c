/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:41:53 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/26 16:55:34 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

int mutex_init(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_phi)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void philo_init(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_phi)
	{
		data->philos[i].finished = 0;
		data->philos[i].got_meals = 0;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		pthread_mutex_init(&data->philos[i].mutex_lmt, NULL);
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_phi];
		data->philos[i].data = data;
		i++;
	}
}

int init_data(t_data *data, char **av)
{
	data->philo_done = 0;
	data->num_meal_flag = 0;
	data->num_meals = 0;
	data->num_phi = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_spleep = ft_atoi(av[4]);
	if (data->num_phi <= 0 || data->time_die <= 0 || data->time_eat <= 0 || data->time_spleep <= 0 || data->num_phi > 2000)
		return (printf("Error: invalid argument or overflow\n"), 1);
	data->death = 0;
	data->start_time = 0;
	data->forks = malloc((data->num_phi * sizeof(pthread_mutex_t)));
	if (!data->forks)
		return (1);
	data->philos = malloc((data->num_phi * sizeof(t_philo)));
	if (!data->philos)
		return (free_forks(data), 1);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_philo_meals, NULL);
	if (mutex_init(data))
		return (1);
	return (0);
}
