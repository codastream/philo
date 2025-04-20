/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 20:15:02 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (NULL);
	data->philosophers = NULL;
	data->forks = NULL;
	data->alive = NULL;
	data->ongoing = NULL;
	data->print = NULL;
	data->start = NULL;
	data->threads = NULL;
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_args(--ac, ++av))
	{
		data = init_data();
		if (!data)
			return (EXIT_FAILURE);
		if (!parse_args(data, ac, av))
		{
			clean(data);
			ft_puterr(MSG_MEM);
			return (EXIT_FAILURE);
		}
		live_love_pray(data);
		clean(data);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_puterr(MSG_USAGE);
		return (EXIT_FAILURE);
	}
}
