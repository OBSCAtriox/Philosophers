/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:24:16 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/19 15:36:31 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void	print_state(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->data->mutex_print);
	if (!ph->data->death)
		printf("\033[107;1;91m%ld %d\033[0m %s\n", timestamp(ph->data), ph->id, msg);
    pthread_mutex_unlock(&ph->data->mutex_print);
}

void	take_forks(t_philo *ph)
{
    if (ph->data->num_phi == 1)
    {
        pthread_mutex_lock(ph->left_fork);
        print_state(ph, TAKE_FORK);
        usleep(ph->data->time_die * 2);
        pthread_mutex_unlock(ph->left_fork);
        print_state(ph, DIED);
        ph->data->death = 1;
        return ;
    }
	else if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->left_fork);
		print_state(ph, TAKE_FORK);
        pthread_mutex_lock(ph->right_fork);
        print_state(ph, TAKE_FORK);
	}
    else
    {
        pthread_mutex_lock(ph->right_fork);
        print_state(ph, TAKE_FORK);
        pthread_mutex_lock(ph->left_fork);
        print_state(ph, TAKE_FORK);
    }
}

void    unlock_forks(t_philo *ph)
{
    if (ph->id % 2 == 0)
    {
        pthread_mutex_unlock(ph->right_fork);
        pthread_mutex_unlock(ph->left_fork);
    }
    else
    {
        pthread_mutex_unlock(ph->left_fork);
        pthread_mutex_unlock(ph->right_fork);
    }
}
