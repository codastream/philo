/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 17:02:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	think(t_phi *phi)
{
	if (!print_activity(phi, MSG_THINK))
		return (false);
	return (true);
}

bool	try_take_forks(t_phi *phi)
{
	if (!print_activity(phi, MSG_FORK))
		return (false);
	if (phi->nb_philo == 1)
		return (false);
	return (true);
}

bool	eat(t_phi *phi)
{
	if (!print_activity(phi, MSG_EAT))
		return (false);
	phi->nb_meals += 1;
	save_time(phi->now);
	phi->last_meal = get_time_ms(phi->now);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!print_activity(phi, MSG_SLEEP))
		return (false);
	usleep(phi->time_to_sleep * 1000);
	move_time(phi->now, phi->time_to_sleep);
	return (true);
}
