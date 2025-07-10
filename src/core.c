/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:51:20 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/23 18:20:12 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finished(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->mutex_dead);
	if (data->dead)
		ret = 1;
	pthread_mutex_unlock(&data->mutex_dead);
	return (ret);
}

static void	get_forks(t_philo *philo, pthread_mutex_t **first,
						pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = &philo->data->forks[philo->id % philo->data->num_philos];
		*second = &philo->data->forks[philo->id - 1];
	}
	else
	{
		*first = &philo->data->forks[philo->id - 1];
		*second = &philo->data->forks[philo->id % philo->data->num_philos];
	}
}

static void	update_meal_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex_meal);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->max_meals != -1
		&& philo->eat_count == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->mutex_finished);
		philo->data->finished_philos++;
		pthread_mutex_unlock(&philo->data->mutex_finished);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork", C_YELLOW);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork", C_YELLOW);
	print_status(philo, "is eating", C_GREEN);
	update_meal_status(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_meal);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].mutex_meal);
		pthread_create(&data->philos[i].thread, NULL,
			&routine, &data->philos[i]);
		ft_usleep(1);
		i++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, data);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
