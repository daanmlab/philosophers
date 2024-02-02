/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:01:12 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/02 15:35:05 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_dead(t_main *main)
{
	t_philo	*philo;

	philo = main->first_philo;
	while (philo)
	{
		_usleep(10);
		if (philo->dead == 0)
			return (0);
		philo = philo->next;
		if (philo == main->first_philo)
			break ;
	}
	return (1);
}

void	*observe(t_main *main)
{
	t_philo		*philo;
	static int	died;

	philo = main->first_philo;
	while (1)
	{
		pthread_mutex_lock(&main->write);
		if (get_time() - philo->last_meal > main->time_to_die)
		{
			died = 1;
			main->dead = 1;
			pthread_mutex_unlock(&main->write);
			break ;
		}
		pthread_mutex_unlock(&main->write);
		philo = philo->next;
	}
	if (died && (philo->meals_eaten < main->nb_meals))
		printf("%llu %d died\n", get_time() - philo->main->start_time, philo->id
			+ 1);
	while (!all_dead(main))
		;
	return (NULL);
}
