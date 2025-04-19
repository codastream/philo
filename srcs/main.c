/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:38 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 14:15:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_args(--ac, ++av))
	{
		data = malloc(1 * sizeof(t_data));
		if (!data)
			return (EXIT_FAILURE);
		if (!parse_args(data, ac, av))
		{
			ft_puterr(MSG_USAGE);
			return (EXIT_FAILURE);
		}
		live_love_pray(data);
		clean(data);
		exit(EXIT_SUCCESS);
	}
	else
		ft_puterr(MSG_USAGE);
}
