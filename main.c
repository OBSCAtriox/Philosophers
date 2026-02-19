/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:26:11 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/19 16:28:51 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/Philo.h"

static int main_help1(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Invalid number of Arguments\n"), 1);
	if (ver_args_valid(av))
		return (printf("Invalid arguments\n"), 1);
	return (0);
}

static int main_help2(t_data *data, int ac, char **av)
{
	if (ac == 5)
		data->num_meal_flag = 1;
	else if (ac == 6)
	{
		data->num_meals = ft_atoi(av[5]);
		if (data->num_meals <= 0)
			return (printf("Invalid meal number"), 1);
	}
	return (0);
}

static int create_philos(t_data *data)
{
	int i = 0;

	while (i < data->num_phi)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		if (!&data->philos[i])
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char *av[])
{
	pthread_t monitor_thread;
	int i;
	t_data data;
	if (main_help1(ac, av))
		return (1);
	if (init_data(&data, av))
		return (cleanup(&data), printf("Init_data Failed\n"), 1);
	philo_init(&data);
	main_help2(&data, ac, av);
	data.start_time = get_time_ms();
	i = 0;
	while (i < data.num_phi)
		data.philos[i++].last_meal_time = data.start_time;
	pthread_create(&monitor_thread, NULL, monitor, &data);
	if (!monitor_thread)
		return (cleanup(&data), 1);
	if (create_philos(&data))
		return (cleanup(&data), 1);
	i = 0;
	while (i < data.num_phi)
		pthread_join(data.philos[i++].thread, NULL);
	cleanup(&data);
	return (0);
}
