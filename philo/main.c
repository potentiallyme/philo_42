/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:52:49 by lmoran            #+#    #+#             */
/*   Updated: 2024/07/11 17:30:26 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num_philo(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **av)
{
	if (ft_atoi_philo(av[1]) > PHILO_MAX || ft_atoi_philo(av[1]) <= 0
		|| is_num_philo(av[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi_philo(av[2]) <= 0 || is_num_philo(av[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi_philo(av[3]) <= 0 || is_num_philo(av[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi_philo(av[4]) <= 0 || is_num_philo(av[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi_philo(av[5]) < 0 || is_num_philo(av[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

void	philo(char **av)
{
	t_data			data;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	init_program(&data, philos);
	init_forks(forks, ft_atoi_philo(av[1]));
	init_philos(philos, &data, forks, av);
	thread_create(&data, forks);
	destory_all(NULL, &data, forks);
}

int	main(int argc, char **av)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(av) == 1)
		return (1);
	philo(av);
	return (0);
}
