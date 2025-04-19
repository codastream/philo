/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:23:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 14:17:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_fork_availability(t_fork *fork)
{
	bool	is_taken;

	pthread_mutex_lock(&fork->fork_m);
	is_taken = fork->is_taken;
	pthread_mutex_unlock(&fork->fork_m);
	return (!is_taken);
}

int	get_nb_meal(t_phi *phi)
{
	int	nb;

	pthread_mutex_lock(&phi->nb_meals->nb_meals_m);
	nb = phi->nb_meals->count;
	pthread_mutex_unlock(&phi->nb_meals->nb_meals_m);
	return (nb);
}

bool	get_ongoing(t_phi *phi)
{
	bool	is_ongoing;

	pthread_mutex_lock(&phi->ongoing->ongoing_m);
	is_ongoing = phi->ongoing->is_ongoing;
	pthread_mutex_unlock(&phi->ongoing->ongoing_m);
	return (is_ongoing);
}

bool	get_all_alive(t_alive *alive)
{
	bool	are_all_alive;

	pthread_mutex_lock(&alive->alive_m);
	are_all_alive = alive->all_alive;
	pthread_mutex_unlock(&alive->alive_m);
	return (are_all_alive);
}

int	get_last_meal(t_phi *phi)
{
	int	last;

	pthread_mutex_lock(&phi->last_meal->last_meal_m);
	last = phi->last_meal->last_meal;
	pthread_mutex_unlock(&phi->last_meal->last_meal_m);
	return (last);
}
