/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:15:04 by lmoran            #+#    #+#             */
/*   Updated: 2024/07/11 17:30:31 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *p, char **av)
{
	p->num_of_philos = ft_atoi_philo(av[1]);
	p->time_to_die = ft_atoi_philo(av[2]);
	p->time_to_eat = ft_atoi_philo(av[3]);
	p->time_to_sleep = ft_atoi_philo(av[4]);
	if (av[5])
		p->num_times_to_eat = ft_atoi_philo(av[5]);
	else
		p->num_times_to_eat = -1;
}

void	init_philos(t_philo *p, t_data *dt, pthread_mutex_t *f, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi_philo(av[1]))
	{
		p[i].id = i + 1;
		p[i].eating = 0;
		p[i].meals_eaten = 0;
		init_input(&p[i], av);
		p[i].last_meal = get_current_time();
		p[i].start_time = get_current_time();
		p[i].dead_flag = &dt->dead_flag;
		p[i].write_lock = &dt->write_lock;
		p[i].dead_lock = &dt->dead_lock;
		p[i].meal_lock = &dt->meal_lock;
		p[i].l_fork = &f[i];
		if (i == 0)
			p[i].r_fork = &f[p[i].num_of_philos - 1];
		else
			p[i].r_fork = &f[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *f, int numof)
{
	int	i;

	i = 0;
	while (i < numof)
	{
		pthread_mutex_init(&f[i], NULL);
		i++;
	}
}

void	init_program(t_data *data, t_philo *p)
{
	data->dead_flag = 0;
	data->philos = p;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}
