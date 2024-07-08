/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:14:49 by lmoran            #+#    #+#             */
/*   Updated: 2024/05/09 11:37:01 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(char *s, t_philo *p, int id)
{
	size_t	time;

	pthread_mutex_lock(p->write_lock);
	time = get_current_time() - p->start_time;
	if (!dead_loop(p))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(p->write_lock);
}

int	is_dead(t_philo *p, size_t time_to_die)
{
	pthread_mutex_lock(p->meal_lock);
	if (get_current_time() - p->last_meal >= time_to_die
		&& p->eating == 0)
		return (pthread_mutex_unlock(p->meal_lock), 1);
	pthread_mutex_unlock(p->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p[0].num_of_philos)
	{
		if (is_dead(&p[i], p[i].time_to_die))
		{
			print_philo("died", &p[i], p[i].id);
			pthread_mutex_lock(p[0].dead_lock);
			*p->dead_flag = 1;
			pthread_mutex_unlock(p[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void print_eat(t_philo *p)
{
	pthread_mutex_lock(p[0].write_lock);
	write(1, "All philosophers have eaten enough\n", 35);
	pthread_mutex_unlock(p[0].write_lock);
}

int	check_if_all_ate(t_philo *p)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (p[0].num_times_to_eat == -1)
		return (0);
	while (i < p[0].num_of_philos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (p[i].meals_eaten >= p[i].num_times_to_eat)
			ate++;
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	if (ate == p[0].num_of_philos)
	{
		pthread_mutex_lock(p[0].dead_lock);
		*p->dead_flag = 1;
		pthread_mutex_unlock(p[0].dead_lock);
		print_eat(p);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
		if (check_if_dead(p) == 1 || check_if_all_ate(p) == 1)
			break ;
	return (ptr);
}
