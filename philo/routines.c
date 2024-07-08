/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:12:16 by lmoran            #+#    #+#             */
/*   Updated: 2024/05/09 11:36:45 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep_think(t_philo *p)
{
	print_philo("is sleeping", p, p->id);
	ft_usleep(p->time_to_sleep);
	print_philo("is thinking", p, p->id);	
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(p->r_fork);
	print_philo("has taken a fork", p, p->id);
	if (p->num_of_philos == 1)
	{
		ft_usleep(p->time_to_die);
		pthread_mutex_unlock(p->r_fork);
		return ;
	}
	pthread_mutex_lock(p->l_fork);
	print_philo("has taken a fork", p, p->id);
	p->eating = 1;
	print_philo("is eating", p, p->id);
	pthread_mutex_lock(p->meal_lock);
	p->last_meal = get_current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	ft_usleep(p->time_to_eat);
	p->eating = 0;
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}
