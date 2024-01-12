/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:01:10 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/09 13:59:56 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int all_done(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo[i].done == 0)
			return (0);
		i++;
	}
	return (1);
}

void	*observer(void *d)
{
	int		i;
	int		count;
	t_data	*data;

	data = (t_data *)d;
	i = 0;
	count = 0;
	while (1)
	{
		if ((data->philo[i].last_meal.tv_sec == 0) || (data->nb_eat != -1
				&& count == data->nb_eat))
			return (NULL);
		if (get_time(data->philo[i].last_meal) > data->time_to_die)
		{
			print(&data->philo[i], "died");
			data->philo[i].done = 1;
			data->dead = 1;
		}
		if (all_done(data))
		{
			// printf("All done\n");
			return (NULL);
		}
		if (++i == data->nb_philo)
		{
			i = 0;
			count++;
		}
	}
	return (NULL);
}

int	setup_dead_observer(t_data *data)
{
	if (pthread_create(&data->observer, NULL, &observer, data))
		return (0);
	return (1);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->dead = 0;
	if (!data->philo)
		return (0);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].nb_meal = 0;
		i++;
	}
	return (1);
}

int	setup(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (!create_philos(data))
		return (0);
	return (1);
}
