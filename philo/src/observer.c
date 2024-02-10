/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:01:12 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/10 16:30:35 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*observe(t_main *main)
{
	t_philo		*philo;
	static int	ate;

	philo = main->first_philo;
	while (1)
	{
		pthread_mutex_lock(&main->write);
		
		if (philo->meals_eaten >= main->nb_meals)
			ate++;
		else 
		{
			ate = 0;
			if (get_time() - philo->last_meal > main->time_to_die)
			{
				main->dead = 1;
				pthread_mutex_unlock(&main->write);
				break ;
			}
		}
		if (ate == main->nb_philo)
		{
			pthread_mutex_unlock(&main->write);
			break ;
		}
		pthread_mutex_unlock(&main->write);
		philo = philo->next;
		usleep(100);
	}
	
	if (philo->meals_eaten < main->nb_meals || main->nb_meals == -1)
		printf("%llu %d died\n", get_time() - philo->main->start_time, philo->id
			+ 1);

	return (NULL);
}
