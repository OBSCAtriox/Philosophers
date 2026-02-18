/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:44:04 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/18 18:25:08 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Philo.h"

int ft_atoi(char *li)
{
	int i;
	int result;
	int sign;

	i = 0;
	sign = 1;
	result = 0;
	while (li[i] == 32 || li[i] == 9)
		i++;
	if (li[i] == '-' || li[i] == '+')
	{
		if (li[i] == '-')
			sign *= -1;
		i++;
	}
	while (li[i] >= '0' && li[i] <= '9')
	{
		result = result * 10 + (li[i] - 48);
		i++;
	}
	return (result * sign);
}

int ver_args_valid(char **av)
{
	int i;
	int j;

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

int ver_valid_timers(int t_eat, int t_die, int t_sleep)
{
	if (t_eat > INT_MAX || t_die > INT_MAX || t_sleep > INT_MAX)
		return (1);
	return (0);
}
