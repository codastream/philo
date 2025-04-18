/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:25:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 19:34:25 by fpetit           ###   ########.fr       */
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
	int	msec_now;

	save_time(phi->now);
	msec_now = phi->now->tv_sec * 1000 + phi->now->tv_usec / 1000;
	phi->last_meal = msec_now;
}
