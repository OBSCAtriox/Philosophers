/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:24:16 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/11 17:30:59 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void	print_state(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->data->mutex_print);
	if (!ph->data->death)
		printf("%ld %d %s\n", timestamp(ph->data), ph->id, msg);
    pthread_mutex_unlock(&ph->data->mutex_print);
}

void	take_forks(t_philo *ph)
{
    if (ph->data->num_phi == 1)
    {
        pthread_mutex_lock(ph->left_fork);
        print_state(ph, "has taken a fork");
    }
	else if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->left_fork);
		print_state(ph, "has taken a fork");
        pthread_mutex_lock(ph->right_fork);
        print_state(ph, "has taken a fork");
	}
    else
    {
        pthread_mutex_lock(ph->right_fork);
        print_state(ph, "has taken a fork");
        pthread_mutex_lock(ph->left_fork);
        print_state(ph, "has taken a fork");
    }
}

void    unlock_forks(t_philo *ph)
{
    if (ph->data->num_phi == 1)
        pthread_mutex_unlock(ph->left_fork);
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
