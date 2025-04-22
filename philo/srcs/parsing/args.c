/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:23:50 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 19:24:07 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fill_args(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->min_nb_meals = UNSET;
	if (ac >= 5)
		data->min_nb_meals = ft_atoi(av[4]);
	data->debug = false;
	if (ac == 6)
		data->debug = true;
}
