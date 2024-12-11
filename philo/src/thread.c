/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:33:01 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 18:17:14 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*th_rou(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_flag(philo) == 1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	philo_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (dead_philo(&data->philos[i]) == 1)
		{
			(ft_message(data->philos[i].start_time, data->philos[i].id,
					"has died", data->philos));
			pthread_mutex_lock(data->philos[0].dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(data->philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_full(t_data *data)
{
	int	i;
	int	full_philo;

	i = 0;
	full_philo = 0;
	if (data->philos[0].num_of_meals == -1)
		return (0);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_lock(data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten > data->philos[i].num_of_meals)
			full_philo++;
		pthread_mutex_unlock(data->philos[i].meal_lock);
		i++;
	}
	if (full_philo == data->philos[0].num_of_philos)
	{
		pthread_mutex_lock(data->philos[0].dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(data->philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*moni_rou(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (philo_died(data) == 1 || philo_full(data) == 1)
			break ;
	}
	return (NULL);
}

void	make_thread(int num_philo, t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &moni_rou, data) != 0)
		error(M_THREAD_ERR, data);
	while (i < num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &th_rou,
				&data->philos[i]) != 0)
			error(THREAD_ERR, data);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		error(JOIN_ERR, data);
	while (i < num_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			error(JOIN_ERR, data);
		i++;
	}
}
