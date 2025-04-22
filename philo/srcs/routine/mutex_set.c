/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:25:29 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 21:32:28 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
