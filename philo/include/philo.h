/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:46:30 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/02 15:20:19 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long	t_ull;

typedef struct s_philo		t_philo;

typedef struct s_main
{
	int						nb_philo;
	int						nb_meals;
	t_ull					time_to_die;
	t_ull					time_to_eat;
	t_ull					time_to_sleep;
	t_ull					start_time;
	int						dead;
	pthread_mutex_t			write;
	pthread_mutex_t			*forks;
	t_philo					*first_philo;
}							t_main;

typedef struct s_philo
{
	int						id;
	int						dead;
	int						meals_eaten;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_ull					last_meal;
	pthread_t				thread;
	t_philo					*next;
	t_main					*main;
}							t_philo;

// utils.c
t_ull						get_time(void);
void						print_status(t_philo *philo, char *status,
								int *dead);
int							ft_atoi(const char *str);
void						_usleep(t_ull time);
int 						is_valid_number(char *str);

// routines.c
void						start_routines(t_main *main);
void						*join_routines(t_main *main);

// philo.c
t_philo						*init_philos(t_main *main);
void						*philo_routine(void *arg);
t_philo						*free_philos(t_philo *philos);
t_philo						*create_philo(t_main *main, int id);

// observer.c
void						*observe(t_main *main);

#endif