/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:55 by tide-pau          #+#    #+#             */
/*   Updated: 2026/03/02 17:22:23 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void	philo_thinking(t_philo *ph)
{
	print_state(ph, THINK);
}

void	philo_sleep(t_philo *ph)
{
	print_state(ph, SLEEP);
	death_sleep(ph->data->time_spleep, ph->data);
}

void	philo_eat(t_philo *ph)
{
	take_forks(ph);
	pthread_mutex_lock(&ph->data->mutex_philo_meals);
	pthread_mutex_lock(&ph->mutex_lmt);
	if (ph->finished == 0)
		ph->got_meals++;
	pthread_mutex_unlock(&ph->data->mutex_philo_meals);
	ph->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&ph->mutex_lmt);
	print_state(ph, EAT);
	death_sleep(ph->data->time_eat, ph->data);
	unlock_forks(ph);
}

int	is_full(t_philo *philo)
{
	if (philo->got_meals == philo->data->num_meals)
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_death);
		if (philo->data->death)
		{
			pthread_mutex_unlock(&philo->data->mutex_death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_death);
		pthread_mutex_lock(&philo->data->mutex_philo_meals);
		if (philo->finished)
		{
			pthread_mutex_unlock(&philo->data->mutex_philo_meals);
			usleep(100);
			continue ;
		}
		pthread_mutex_unlock(&philo->data->mutex_philo_meals);
		eat_sleep_think(philo);
		if (philo->data->num_meal_flag == 0)
			routine_help(philo);
	}
	return (NULL);
}
