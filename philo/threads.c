/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:16:24 by lmoran            #+#    #+#             */
/*   Updated: 2024/05/09 11:36:38 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *p)
{
	pthread_mutex_lock(p->dead_lock);
	if (*p->dead_flag == 1)
		return (pthread_mutex_unlock(p->dead_lock), 1);
	pthread_mutex_unlock(p->dead_lock);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		sleep_think(philo);
	}
	return (ptr);
}

int	thread_create(t_data *data, pthread_mutex_t *f)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		destory_all("Thread creation error", data, f);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			destory_all("Thread creation error", data, f);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", data, f);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", data, f);
		i++;
	}
	return (0);
}
