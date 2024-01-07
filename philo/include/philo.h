/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:46:30 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/07 23:37:26 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_data t_data;

typedef struct s_philo
{
    int id;
    pthread_t thread;
    struct timeval last_meal;
    int nb_meal;
    t_data *data;
    
}              t_philo;

typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;
    int dead;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_t observer;
    t_philo *philo;
}              t_data;

#endif