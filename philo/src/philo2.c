/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:02:01 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/30 20:03:30 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_main *main, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->dead = 0;
	philo->meals_eaten = 0;
	philo->last_meal = main->start_time;
	philo->main = main;
	philo->next = NULL;
	philo->left_fork = &main->forks[id];
	philo->right_fork = &main->forks[(id + 1) % main->nb_philo];
	return (philo);
}

t_philo	*free_philos(t_philo *philos)
{
	t_philo	*tmp;
	int		i;

	i = philos->main->nb_philo;
	while (i--)
	{
		tmp = philos->next;
		free(philos);
		philos = tmp;
	}
	return (NULL);
}
