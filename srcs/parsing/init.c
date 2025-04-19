/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:46:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 14:17:32 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_nb_meals	*init_nb_meals(t_data *data)
{
	t_nb_meals	*nb_meals;

	nb_meals = malloc(1 * sizeof(t_nb_meals));
	check_malloc(data, nb_meals);
	if (pthread_mutex_init(&nb_meals->nb_meals_m, NULL) != 0)
	{
		free(nb_meals);
		return (NULL);
	}
	nb_meals->count = 0;
	return (nb_meals);
}

t_print	*init_print(t_data *data)
{
	t_print	*print;

	print = malloc(1 * sizeof(t_print));
	check_malloc(data, print);
	if (pthread_mutex_init(&print->print_m, NULL) != 0)
	{
		free(print);
		return (NULL);
	}
	print->can_print = true;
	return (print);
}

t_ongoing	*init_ongoing(t_data *data)
{
	t_ongoing	*ongoing;

	ongoing = malloc(1 * sizeof(t_ongoing));
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
	check_malloc(data, alive);
	if (pthread_mutex_init(&alive->alive_m, NULL) != 0)
	{
		free(alive);
		return (NULL);
	}
	alive->all_alive = true;
	return (alive);
}
