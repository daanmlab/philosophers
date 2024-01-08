/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:06:14 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/08 00:06:02 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	gettimeofday(&philo->last_meal, NULL);
	while (1)
	{
		print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->nb_philo]);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		usleep(philo->data->time_to_eat);
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->nb_philo]);
		if (philo->data->nb_eat != -1 && philo->nb_meal == philo->data->nb_eat)
			return (NULL);
		print(philo, "is sleeping");
		usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]))
			return ;
		i++;
	}
}

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (!check_args(argc, argv))
	{
		printf("Error: bad arguments\n");
		return (0);
	}
	if (!setup(&data, argc, argv))
	{
		printf("Error: setup failed\n");
		return (0);
	}
	while (i < data.nb_philo)
		data.philo[i++].last_meal = (struct timeval){0, 0};
	if (!setup_dead_observer(&data))
	{
		printf("Error: setup failed\n");
		return (0);
	}
	start(&data);
	join_philos(&data);
	return (0);
}
