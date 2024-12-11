/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastian <abastian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:24:41 by abastian          #+#    #+#             */
/*   Updated: 2024/12/10 18:11:19 by abastian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	parse_check(int argc, char **argv, int i, t_data *data)
{
	int	j;

	if (argc < 5 || argc > 6)
		error(WRONG_NUM, data);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	value_check(char **argv, int i, int nbr)
{
	while (argv[i])
	{
		nbr = ft_atoi(argv[i]);
		if (nbr <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	forks[PHILO_MAX];

	if (!parse_check(argc, argv, 1, &data))
		error(PARS_ERR, &data);
	if (!value_check(argv, 1, 0))
		error(VALUE_ERR, &data);
	init_data_and_forks(forks, ft_atoi(argv[1]), 0, &data);
	if (argc == 6)
		init_philo(forks, ft_atoi(argv[5]), argv, &data);
	else
		init_philo(forks, -1, argv, &data);
	make_thread(ft_atoi(argv[1]), &data);
	destroy_mutexs(&data, forks);
	return (0);
}

// void	print_philo(int num, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while(i < num)
// 	{
// 		printf("PHILO ATTENDU NUMERO %d :\n\n", i + 1);
// 		printf("ID PHILO : %d\n", data->philos[i].id);
// 		printf("TIME TO DIE : %zu\n", data->philos[i].time_to_die);
// 		printf("TIME TO EAT : %zu\n", data->philos[i].time_to_eat);
// 		printf("TIME TO SLEEP : %zu\n", data->philos[i].time_to_sleep);
// 		printf("NUM OF MEALS : %d\n", data->philos[i].num_of_meals);
// 		printf("START_TIME : %zu\n", data->philos[i].start_time);
// 		printf("LAST_MEAL : %zu\n", data->philos[i].last_meal);
// 		printf("L_FORK : %p\n", (void *)data->philos[i].l_fork);
// 		printf("R_FORK : %p\n", (void *)data->philos[i].r_fork);
// 		printf("WRITE_LOCK : %p\n", (void *)data->philos[i].write_lock);
// 		printf("MEAL_LOCK : %p\n", (void *)data->philos[i].meal_lock);
// 		printf("DEAD_LOCK : %p\n\n", (void *)data->philos[i].dead_lock);
// 		i++;
// 	}
// }
