/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:46:30 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/08 15:05:32 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	struct timeval		last_meal;
	int					nb_meal;
	t_data				*data;
	int					start;
	int 				done;
}						t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_t			observer;
	t_philo				*philo;
}						t_data;

int						ft_atoi(char *str);
void					print(t_philo *philo, char *str);
int						check_args(int argc, char **argv);
int						get_time(struct timeval last_meal);

int						setup_dead_observer(t_data *data);
void					*observer(void *d);
int						create_philos(t_data *data);
int						setup(t_data *data, int argc, char **argv);
void end(t_data *data);

#endif