/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/05 16:44:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (check_args(--ac, ++av))
	{
		t_data	*data;
		data = malloc(1 * sizeof(t_data));
		if (!data)
			return (EXIT_FAILURE);
		parse_args(data, ac, av);
		save_start(data);
		clean(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_puterr("usage: philo <number_of_philosophers>\n<time_to_die>\n<time_to_eat>\n<time_to_sleep>\n[number_of_times_each_philosopher_must_eat]\n");
	}
}

