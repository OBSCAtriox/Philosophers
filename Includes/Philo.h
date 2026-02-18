/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:14:00 by tide-pau          #+#    #+#             */
/*   Updated: 2026/02/11 17:14:50 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define TRUE = 1
# define FALSE = 0

typedef struct s_philo t_philo;

typedef struct s_data
{
    int num_phi;
    long time_die;
    long time_eat;
    long time_spleep;
    long start_time;
    int death;
    pthread_mutex_t mutex_print;
    pthread_mutex_t mutex_death;
    pthread_mutex_t *forks;
    t_philo *philos;
    
}	t_data;

typedef struct s_philo
{
    int id;
    long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
}   t_philo;

// init.c
int mutex_init(t_data *data);
void philo_init(t_data *data);
int	init_data(t_data *data, char **av);

// routine.c
void    philo_thinking(t_philo *ph);
void    philo_sleep(t_philo *ph);
void	philo_eat(t_philo *ph);
void    *routine(void *arg);

// monitor.c
void    *monitor(void *arg);
void    monitor_helper(t_data *data, int i);

// utils_1.c
int ver_valid_timers(int t_eat, int t_die, int t_sleep);
int ft_atoi(char *li);
int	ver_args_valid(char **av);

// utils_2.c
long get_time_ms(void);
long timestamp(t_data *data);
void    death_sleep(long ms, t_data *data);

// utils_3.c
void	print_state(t_philo *ph, char *msg);
void	take_forks(t_philo *ph);
void    unlock_forks(t_philo *ph);

// free.c
void    cleanup(t_data *data);
void    free_philos(t_data *data);
void    free_forks(t_data *data);

#endif