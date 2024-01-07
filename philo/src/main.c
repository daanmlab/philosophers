/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:06:14 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/07 23:38:33 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while (str[i])
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res);
}


void print(t_philo *philo, char *str)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (philo->data->dead)
        return ;
    pthread_mutex_lock(&philo->data->print);
    printf("%ld:%ld %d %s\n", tv.tv_sec, tv.tv_usec, philo->id, str);
    pthread_mutex_unlock(&philo->data->print);
}

int check_args(int argc, char **argv)
{
    int i;
    int j;

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

int get_time(struct timeval last_meal)
{
    struct timeval tv;
    int res;

    gettimeofday(&tv, NULL);
    res = (tv.tv_sec - last_meal.tv_sec) * 1000;
    res += (tv.tv_usec - last_meal.tv_usec) / 1000;
    return (res);
}
void *observer(void *d)
{
    int i;
    int count;
    t_data *data;

    data = (t_data *)d;

    i = 0;
    count = 0;
    while (1)
    {
        if ((data->philo[i].last_meal.tv_sec == 0) || (data->nb_eat != -1 && count == data->nb_eat))
            return NULL;
        if (get_time(data->philo[i].last_meal) > data->time_to_die)
        {
            print(&data->philo[i], "died");
            data->dead = 1;
            exit(0);
        }
        i++;
        if (i == data->nb_philo)
        {
            i = 0;
            count++;
        }
    }
    return NULL;
}

int setup_dead_observer(t_data *data)
{
    if (pthread_create(&data->observer, NULL, &observer, data))
        return (0);
    return (1);
}

int create_philos(t_data *data)
{
    int i;

    i = 0;
    data->philo = malloc(sizeof(t_philo) * data->nb_philo);
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

int setup(t_data *data, int argc, char **argv)
{
    int i;

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
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (0);
        i++;
    }
    if (pthread_mutex_init(&data->print, NULL))
        return (0);
    if (!create_philos(data))
        return (0);
    return (1);
}


void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; 
    gettimeofday(&philo->last_meal, NULL);
    while (1)
    {
        print(philo, "is thinking");
        pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
        print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nb_philo]);
        print(philo, "has taken a fork");
        print(philo, "is eating");
        usleep(philo->data->time_to_eat);
        philo->nb_meal++;
        pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
        pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_philo]);
        if(philo->data->nb_eat != -1 && philo->nb_meal == philo->data->nb_eat)
            return (NULL);
        print(philo, "is sleeping");
        usleep(philo->data->time_to_sleep);
    }
    return (NULL);
}
void start(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].data = data;
        if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]))
            return ;
        i++;
    }
}

void join_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_join(data->philo[i].thread, NULL))
            return ;
        i++;
    }
}

int main(int argc, char **argv)
{
    t_data data;
    int i;

    i = 0;
    if(!check_args(argc, argv))
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
