/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:42:37 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/30 19:42:57 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_routines(t_main *main)
{
	t_philo	*philo;

	philo = main->first_philo;
	while (philo)
	{
		if (philo->id % 2 == 0)
		{
			pthread_create(&philo->thread, NULL, philo_routine, philo);
		}
		philo = philo->next;
		if (philo == main->first_philo)
			break ;
	}
	_usleep(50);
	philo = main->first_philo->next;
	while (philo)
	{
		if (philo->id % 2 == 1)
		{
			pthread_create(&philo->thread, NULL, philo_routine, philo);
		}
		philo = philo->next;
		if (philo == main->first_philo)
			break ;
	}
}

void	*join_routines(t_main *main)
{
	t_philo	*philo;

	philo = main->first_philo;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (philo == main->first_philo)
			break ;
	}
	return (NULL);
}
