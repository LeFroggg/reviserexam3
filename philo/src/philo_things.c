/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:06:10 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 17:50:45 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_message(philo->start_time, philo->id, "has taken a fork", philo);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo->start_time, philo->id, "has taken a fork", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_message(philo->start_time, philo->id, "is eating", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	ft_message(philo->start_time, philo->id, "is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	ft_message(philo->start_time, philo->id, "is thinking", philo);
}
