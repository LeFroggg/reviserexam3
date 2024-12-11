/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:14:35 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 18:15:00 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

void	error(char *msg, t_data *data)
{
	(void)data;
	printf("%s\n", msg);
	exit(1); // PUTAIN
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(TIME_ERR);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_message(size_t time_start, int id, char *msg, t_philo *philo)
{
	if (!check_flag(philo))
		return ;
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", (get_current_time() - time_start), id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	destroy_mutexs(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
