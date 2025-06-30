/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:50:12 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/30 11:50:12 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_finished(philo->data))
	{
		eat(philo);
		if (philo->data->num_philos == 1)
			break ;
		print_status(philo, "is sleeping", C_BLUE);
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking", C_CYAN);
	}
	return (NULL);
}
