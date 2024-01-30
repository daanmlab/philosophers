/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:48:16 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/30 20:04:09 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ull	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status, int *dead)
{
	pthread_mutex_lock(&philo->main->write);
	if (philo->main->dead)
	{
		pthread_mutex_unlock(&philo->main->write);
		*dead = 1;
		return ;
	}
	pthread_mutex_unlock(&philo->main->write);
	printf("%llu %d %s\n", get_time() - philo->main->start_time, philo->id + 1,
		status);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	_usleep(t_ull time)
{
	t_ull	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}
