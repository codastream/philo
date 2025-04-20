/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:46:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 20:27:31 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_nb_meals	*init_nb_meals(t_data *data)
{
	t_nb_meals	*nb_meals;

	nb_meals = malloc(1 * sizeof(t_nb_meals));
	if (!nb_meals)
		return (NULL);
	check_malloc(data, nb_meals);
	if (pthread_mutex_init(&nb_meals->nb_meals_m, NULL) != 0)
	{
		free(nb_meals);
		return (NULL);
	}
	nb_meals->count = 0;
	return (nb_meals);
}

t_ongoing	*init_ongoing(t_data *data)
{
	t_ongoing	*ongoing;

	ongoing = malloc(1 * sizeof(t_ongoing));
	if (!ongoing)
		return (NULL);
	check_malloc(data, ongoing);
	if (pthread_mutex_init(&ongoing->ongoing_m, NULL) != 0)
	{
		free(ongoing);
		return (NULL);
	}
	ongoing->is_ongoing = true;
	return (ongoing);
}

t_last_meal	*init_last_meal(t_phi *phi)
{
	t_last_meal	*last_meal;

	last_meal = malloc(1 * sizeof(t_last_meal));
	if (!last_meal)
		return (NULL);
	if (pthread_mutex_init(&last_meal->last_meal_m, NULL) != 0)
	{
		free(last_meal);
		return (NULL);
	}
	last_meal->last_meal = get_time_ms(phi->start);
	return (last_meal);
}

t_alive	*init_alive(t_data *data)
{
	t_alive	*alive;

	alive = malloc(1 * sizeof(t_alive));
	if (!alive)
		return (NULL);
	check_malloc(data, alive);
	if (pthread_mutex_init(&alive->alive_m, NULL) != 0)
	{
		free(alive);
		return (NULL);
	}
	alive->all_alive = true;
	return (alive);
}

void	fill_args(t_data **data, int ac, char **av)
{
	(*data)->nb_philo = ft_atoi(av[0]);
	(*data)->time_to_die = ft_atoi(av[1]);
	(*data)->time_to_eat = ft_atoi(av[2]);
	(*data)->time_to_sleep = ft_atoi(av[3]);
	(*data)->min_nb_meals = UNSET;
	if (ac >= 5)
		(*data)->min_nb_meals = ft_atoi(av[4]);
	(*data)->debug = false;
	if (ac == 6)
		(*data)->debug = true;
}
