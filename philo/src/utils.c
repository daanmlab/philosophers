/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:58:08 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/09 14:21:19 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

void	print(t_philo *philo, char *str)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->dead)
		printf("%ld %d %s\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000), philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_time(struct timeval last_meal)
{
	struct timeval	tv;
	int				res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec - last_meal.tv_sec) * 1000;
	res += (tv.tv_usec - last_meal.tv_usec) / 1000;
	return (res);
}

void end(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    free(data->forks);
    free(data->philo);
    exit(0);
}