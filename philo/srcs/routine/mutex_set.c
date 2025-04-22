/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:25:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 21:56:40 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_status(t_fork *fork, bool is_taken)
{
	pthread_mutex_lock(&fork->fork_m);
	fork->is_taken = is_taken;
	pthread_mutex_unlock(&fork->fork_m);
}

void	set_is_ongoing(t_ongoing *ongoing, bool is_ongoing)
{
	pthread_mutex_lock(&ongoing->ongoing_m);
	ongoing->is_ongoing = is_ongoing;
	pthread_mutex_unlock(&ongoing->ongoing_m);
}

void	set_nb_meal_plus(t_nb_meals *meals)
{
	pthread_mutex_lock(&meals->nb_meals_m);
	meals->count += 1;
	pthread_mutex_unlock(&meals->nb_meals_m);
}

void	update_last_meal(t_phi *phi)
{
	pthread_mutex_lock(&phi->last_meal->last_meal_m);
	save_time(phi->now);
	phi->last_meal->last_meal = get_time_ms(phi->now);
	pthread_mutex_unlock(&phi->last_meal->last_meal_m);
}

void	set_death(t_alive *alive)
{
	pthread_mutex_lock(&alive->alive_m);
	alive->all_alive = false;
	pthread_mutex_unlock(&alive->alive_m);
}
