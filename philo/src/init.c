/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:10:17 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 18:32:26 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_data_and_forks(pthread_mutex_t *f, int phi, int i, t_data *data)
{
	data->dead_flag = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	while (i < phi)
	{
		pthread_mutex_init(&f[i], NULL);
		i++;
	}
}

void	init_philo(pthread_mutex_t *f, int num_eat, char **argv, t_data *data)
{
	int	i;

	i = -1;
	while (i++ < ft_atoi(argv[1]))
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = (size_t)ft_atoi(argv[2]);
		data->philos[i].time_to_eat = (size_t)ft_atoi(argv[3]);
		data->philos[i].time_to_sleep = (size_t)ft_atoi(argv[4]);
		data->philos[i].num_of_philos = ft_atoi(argv[1]);
		data->philos[i].num_of_meals = num_eat;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].start_time = get_current_time();
		data->philos[i].dead = &data->dead_flag;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].meal_lock = &data->meal_lock;
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].l_fork = &f[i];
		if (i == 0)
			data->philos[i].r_fork = &f[ft_atoi(argv[1]) - 1];
		else
			data->philos[i].r_fork = &f[i - 1];
	}
}

int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (philo->eating == 0 && (get_current_time()
			- philo->last_meal) >= philo->time_to_die)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
