/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:58:28 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/04 02:08:50 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @returns a circular linked list of philos
 * @returns NULL if malloc fails
*/
t_philo	*init_philos(t_main *main)
{
	t_philo	*philos;
	t_philo	*philo;
	int		i;

	i = 0;
	philos = NULL;
	philo = NULL;
	while (i < main->nb_philo)
	{
		if (philo)
		{
			philo->next = create_philo(main, i);
			philo = philo->next;
		}
		else
			philo = create_philo(main, i);
		if (!philo)
			return (free_philos(philos));
		if (!philos)
			philos = philo;
		philo->next = philos;
		i++;
	}
	philo->next = philos;
	return (philos);
}

void	unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (left_fork)
		pthread_mutex_unlock(left_fork);
	if (right_fork)
		pthread_mutex_unlock(right_fork);
}

void	take_forks(t_philo *philo, int *dead)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", dead);
		if (*dead || philo->main->nb_philo == 1)
		{
			*dead = 1;
			return (unlock_forks(philo->left_fork, NULL));
		}
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", dead);
		if (*dead)
			unlock_forks(philo->left_fork, philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", dead);
	if (*dead)
		return (unlock_forks(NULL, philo->right_fork));
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", dead);
	if (*dead)
		unlock_forks(philo->left_fork, philo->right_fork);
}

int	eat(t_philo *philo, int *dead)
{
	take_forks(philo, dead);
	if (*dead)
		return (0);
	print_status(philo, "is eating", dead);
	pthread_mutex_lock(&philo->main->write);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->main->write);
	_usleep(philo->main->time_to_eat);
	unlock_forks(philo->left_fork, philo->right_fork);
	philo->meals_eaten++;
	if ((philo->main->nb_meals != -1
			&& philo->meals_eaten >= philo->main->nb_meals) || *dead)
		return (0);
	return (1);
}

int is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->write);
	if (philo->main->dead)
	{
		pthread_mutex_unlock(&philo->main->write);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->write);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		dead;

	dead = 0;
	philo = (t_philo *)arg;
	while (!philo->dead)
	{
		if (is_dead(philo))
			break ;
		if (!eat(philo, &dead))
			break ;
		print_status(philo, "is sleeping", &dead);
		_usleep(philo->main->time_to_sleep);
		if (is_dead(philo))
			break ;
		print_status(philo, "is thinking", &dead);
	}
	return (NULL);
}
