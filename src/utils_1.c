/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:44:04 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/26 17:04:28 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

int	ft_atoi(char *li)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (li[i] == 32 || li[i] == 9)
		i++;
	if (li[i] == '+')
		i++;
	if (li[i] == '-')
		return (-1);
	while (li[i] >= '0' && li[i] <= '9')
	{
		result = result * 10 + (li[i] - 48);
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (li[i] != '\0')
		return (-1);
	return ((int)result);
}

int	ver_args_valid(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ver_valid_timers(int t_eat, int t_die, int t_sleep)
{
	if (t_eat > INT_MAX || t_die > INT_MAX || t_sleep > INT_MAX)
		return (1);
	if (t_eat <= 0 || t_die <= 0 || t_sleep <= 0)
		return (1);
	return (0);
}

void	eat_sleep_think(t_philo *philo)
{
	philo_eat(philo);
	philo_sleep(philo);
	philo_thinking(philo);
}

int	routine_help(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_philo_meals);
	if (!philo->finished && is_full(philo))
	{
		philo->finished = 1;
		philo->data->philo_done++;
		pthread_mutex_unlock(&philo->data->mutex_philo_meals);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_philo_meals);
	return (0);
}
