/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:04:02 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 18:17:27 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PARS_ERR "At least one argument is wrong"
# define WRONG_NUM "You need only 4 ou 5 arguments"
# define VALUE_ERR "Each argument should be superior than 0 / Too much philos"
# define TIME_ERR "An error has occured from gettimeofday() function"
# define THREAD_ERR "Error while creating threads"
# define M_THREAD_ERR "Error while creating monitor's thread"
# define JOIN_ERR "Error while trying to join threads together"

# define PHILO_MAX 250

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_of_meals;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			philos[PHILO_MAX];
}					t_data;

int		ft_atoi(const char *nptr);
void	error(char *msg, t_data *data);
void	init_philo(pthread_mutex_t *f, int num_eat, char **argv, t_data *data);
void	init_data_and_forks(pthread_mutex_t *f, int phi, int i, t_data *data);
size_t	get_current_time(void);
void	make_thread(int num_philo, t_data *data);
void	ft_message(size_t time_start, int philo_id, char *msg, t_philo *philo);
int		ft_usleep(size_t milliseconds);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	destroy_mutexs(t_data *data, pthread_mutex_t *forks);
int		check_flag(t_philo *philo);
int		dead_philo(t_philo *philo);

#endif
