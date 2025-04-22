/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 21:25:15 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->philosophers = NULL;
	data->forks = NULL;
	data->alive = NULL;
	data->ongoing = NULL;
	data->start = NULL;
	data->threads = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(--ac, ++av))
	{
		init_data(&data);
		if (!parse_args(&data, ac, av))
		{
			clean(&data);
			ft_puterr(MSG_MEM);
			return (EXIT_FAILURE);
		}
		live_love_pray(&data);
		clean(&data);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_puterr(MSG_USAGE);
		return (EXIT_FAILURE);
	}
}
