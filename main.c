/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:26:11 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/11 17:37:01 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/Philo.h"

int	main(int ac, char *av[])
{
	pthread_t monitor_thread;
	t_data	data;
	int		i;

	if (ac != 5)
		return (printf("Invalid number of Arguments\n"), 1);
	if (ver_args_valid(av))
		return (printf("Invalid arguments\n"), 1);
	if (init_data(&data, av))
		return (printf("Init_data Failed\n"), 1);
	philo_init(&data);
	data.start_time = get_time_ms();
	i = 0;
	while (i < data.num_phi)
		data.philos[i++].last_meal_time = data.start_time;
	pthread_create(&monitor_thread, NULL, monitor, &data);
	i = 0;
	while (i < data.num_phi)
	{
		pthread_create(&data.philos[i].thread, NULL, routine, &data.philos[i]);
		i++;
	}
    i = 0;
    while (i < data.num_phi)
        pthread_join(data.philos[i++].thread, NULL);
    cleanup(&data);
    return (0);
}
