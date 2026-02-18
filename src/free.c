/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:24:16 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/11 15:55:29 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/Philo.h"

void    cleanup(t_data *data)
{
    if (!data)
        return ;
    pthread_mutex_destroy(&data->mutex_print);
    pthread_mutex_destroy(&data->mutex_death);
    free_forks(data);
    free_philos(data);
}

void    free_philos(t_data *data)
{
    if (!data || !data->philos)
        return ;
    free(data->philos);
    data->philos = NULL;
}

void    free_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_phi)
        pthread_mutex_destroy(&data->forks[i++]);
    free(data->forks);
    data->forks = NULL;
}
