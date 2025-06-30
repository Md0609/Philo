/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:45:12 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/30 11:45:12 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->mutex_meal);
	time = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->mutex_meal);
	if (time >= philo->data->time_to_die)
		return (1);
	return (0);
}

static int	any_philo_died(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (check_death(&data->philos[i]))
		{
			print_status(&data->philos[i], "died", C_RED);
			pthread_mutex_lock(&data->mutex_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->mutex_dead);
			return (1);
		}
	}
	return (0);
}

static int	all_philos_ate(t_data *data)
{
	if (data->max_meals == -1)
		return (0);
	pthread_mutex_lock(&data->mutex_finished);
	if (data->finished_philos >= data->num_philos)
	{
		pthread_mutex_unlock(&data->mutex_finished);
		pthread_mutex_lock(&data->mutex_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finished);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (any_philo_died(data) || all_philos_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
