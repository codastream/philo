/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:32:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 19:57:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	extend_time_to_die(t_die *die, t_phi *phi)
{
	pthread_mutex_lock(&die->timedie_m);
	die->timedie = get_now(phi->now) + phi->time_to_eat;
	pthread_mutex_unlock(&die->timedie_m);
}

int		get_timedie(t_die *die)
{
	int	ms;

	pthread_mutex_lock(&die->timedie_m);
	ms = die->timedie;
	pthread_mutex_unlock(&die->timedie_m);
	return (ms);
}

void	set_death(t_alive *alive)
{
	pthread_mutex_lock(&alive->alive_m);
	alive->all_alive = false;
	pthread_mutex_unlock(&alive->alive_m);
}
