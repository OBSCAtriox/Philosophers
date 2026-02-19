/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:55 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/19 16:36:47 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

void philo_thinking(t_philo *ph)
{
    long time_util;
    long time_think;

    time_util = (ph->data->time_eat + ph->data->time_spleep);
    time_think = (ph->data->time_die - time_util) / 2;
    if (time_think < 0)
        time_think = 0;
    print_state(ph, THINK);
    death_sleep(time_think, ph->data);
}

void philo_sleep(t_philo *ph)
{
    print_state(ph, SLEEP);
    death_sleep(ph->data->time_spleep, ph->data);
}

void philo_eat(t_philo *ph)
{
    pthread_mutex_lock(&ph->data->mutex_death);
    ph->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&ph->data->mutex_death);
    take_forks(ph);
    print_state(ph, EAT);
    ph->got_meals++;
    death_sleep(ph->data->time_eat, ph->data);
    unlock_forks(ph);
}

int is_full(t_philo *philo)
{
    if (philo->got_meals >= philo->data->num_meals)
        return (1);
    return (0);
}

void *routine(void *arg)
{
    t_philo *philo;

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
        if (philo->data->num_meal_flag == 0)
            if (is_full(philo))
            {
                pthread_mutex_lock(&philo->data->mutex_philo_meals);
                philo->data->philo_done++;
                pthread_mutex_lock(&philo->data->mutex_philo_meals);
                break ;
            }
        philo_eat(philo);
        philo_sleep(philo);
        philo_thinking(philo);
    }
    return (NULL);
}
