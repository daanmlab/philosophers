/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:43:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/30 19:42:47 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
		pthread_mutex_init(&main->forks[i++], NULL);
	pthread_mutex_init(&main->write, NULL);
}

void	init_main(t_main *main, int argc, char **argv)
{
	main->nb_philo = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main->nb_meals = ft_atoi(argv[5]);
	else
		main->nb_meals = -1;
	main->start_time = get_time();
	main->forks = malloc(sizeof(pthread_mutex_t) * main->nb_philo);
	main->first_philo = init_philos(main);
	main->dead = 0;
}

void	*destroy_main(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
		pthread_mutex_destroy(&main->forks[i++]);
	free(main->forks);
	pthread_mutex_destroy(&main->write);
	return (NULL);
}

int	main(int argc, char **argv)
{
	struct s_main	main;

	if ((argc < 5 || argc > 6) && printf("Wrong number of arguments\n"))
		return (1);
	init_main(&main, argc, argv);
	init_mutexes(&main);
	start_routines(&main);
	observe(&main);
	join_routines(&main);
	free_philos(main.first_philo);
	destroy_main(&main);
	return (0);
}
