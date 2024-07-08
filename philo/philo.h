/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:16:37 by lmoran            #+#    #+#             */
/*   Updated: 2024/07/08 12:34:40 by lmoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	// * philo
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	// * return gettime
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	size_t			start_time;
	// * pointer to data
	int				*dead_flag;
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
	t_philo			*philos;
}					t_data;

// * Main
int					check_arg_content(char *arg);
int					check_valid_args(char **argv);
void				destory_all(char *str, t_data *data,
						pthread_mutex_t *forks);

// * Init
void				init_program(t_data *data, t_philo *p);
void				init_forks(pthread_mutex_t *f, int numof);
void				init_philos(t_philo *p, t_data *dt,
						pthread_mutex_t *f, char **av);
void				init_input(t_philo *p, char **av);

// * Threads
int					thread_create(t_data *data, pthread_mutex_t *f);
void				*philo_routine(void *pointer);

// * Routines
void				eat(t_philo *p);
void				sleep_think(t_philo *p);

// * Monitor
int					dead_loop(t_philo *p);
int					check_if_all_ate(t_philo *p);
int					check_if_dead(t_philo *p);
int					is_dead(t_philo *p, size_t time_to_die);
void				*monitor(void *ptr);

// * Utils
int					ft_atoi_philo(char *str);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				print_philo(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

#endif
