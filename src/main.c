/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:51:36 by mdios-el          #+#    #+#             */
/*   Updated: 2025/06/23 16:51:36 by mdios-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	num_philos;

	num_philos = ft_atoi(argv[1]);
	if (num_philos < 1 || num_philos > 200)
		return (0);
	i = 2;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (ft_error("Invalid number of arguments"));
	if (!check_args(argc, argv))
		return (ft_error("Invalid arguments"));
	data = init_data(argc, argv);
	if (!data)
		return (ft_error("Initialization failed"));
	start_simulation(data);
	cleanup(data);
	return (0);
}
