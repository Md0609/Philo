/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:11:05 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/23 16:50:01 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// Colors
# define C_RESET "\033[0m"
# define C_RED "\033[0;31m"
# define C_GREEN "\033[0;32m"
# define C_YELLOW "\033[0;33m"
# define C_BLUE "\033[0;34m"
# define C_CYAN "\033[0;36m"

// Structs

struct s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eat_count;
	long long		last_meal;
	struct s_data	*data;
	pthread_mutex_t	mutex_meal;
}t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				dead;
	int				finished_philos;
	t_philo			*philos;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_finished;
}t_data;

// Main
int			check_args(int argc, char **argv);

// Init
t_data		*init_data(int argc, char **argv);

// Core
void		start_simulation(t_data *data);
void		eat(t_philo *philo);
int			is_finished(t_data *data);

// Monitor
void		*monitor(void *arg);

// Routine
void		*routine(void *arg);

// Utils
int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(long long time_ms);
void		print_status(t_philo *philo, char *status, char *color);
int			ft_error(char *msg);
void		cleanup(t_data *data);

#endif