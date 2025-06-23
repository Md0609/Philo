/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:50:31 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/23 16:50:31 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res > INT_MAX)
			return (-1);
		str++;
	}
	return ((int)res);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_ms)
		usleep(500);
}

void	print_status(t_philo *philo, char *status, char *color)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%s%lld %d %s%s\n", color, get_time() - philo->data->start_time, 
			philo->id, status, C_RESET);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
}

int	ft_error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

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