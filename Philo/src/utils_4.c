/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:43:54 by tide-pau          #+#    #+#             */
/*   Updated: 2026/03/03 17:15:10 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

int	if_philo_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_philo_meals);
	if (philo->finished)
	{
		pthread_mutex_unlock(&philo->data->mutex_philo_meals);
		usleep(100);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_philo_meals);
	return (0);
}
