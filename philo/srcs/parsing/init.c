/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:46:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 20:10:52 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_nb_meals	*init_nb_meals(void)
{
	t_nb_meals	*nb_meals;

	nb_meals = malloc(1 * sizeof(t_nb_meals));
	if (!nb_meals)
		return (NULL);
	if (pthread_mutex_init(&nb_meals->nb_meals_m, NULL) != 0)
	{
		free(nb_meals);
		return (NULL);
	}
	nb_meals->count = 0;
	return (nb_meals);
}

t_ongoing	*init_ongoing(void)
{
	t_ongoing	*ongoing;

	ongoing = malloc(1 * sizeof(t_ongoing));
	if (!ongoing)
		return (NULL);
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

t_alive	*init_alive(void)
{
	t_alive	*alive;

	alive = malloc(1 * sizeof(t_alive));
	if (!alive)
		return (NULL);
	if (pthread_mutex_init(&alive->alive_m, NULL) != 0)
	{
		free(alive);
		return (NULL);
	}
	alive->all_alive = true;
	return (alive);
}

t_die *init_timedie(int ms)
{
	t_die	*timedie;

	timedie = malloc(1 * sizeof(t_die));
	if (!timedie)
		return (NULL);
	if (pthread_mutex_init(&timedie->timedie_m, NULL) != 0)
	{
		free(timedie);
		return (NULL);
	}
	timedie->timedie = get_current_time_ms() + ms;
	return (timedie);
}
