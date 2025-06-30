/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:38:21 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/30 11:38:21 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_meal);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_finished);
	free(data->philos);
	free(data->forks);
	free(data);
}
