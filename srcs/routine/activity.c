/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 13:57:16 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	think(t_phi *phi, int i_left)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_THINK))
		return (false);
	while (!get_fork_availability(phi->forks[i_left]))
	{
		usleep(30);
		move_time(phi->now, 30);
	}
	return (true);
}

bool	try_take_forks(t_phi *phi, int i_left, int i_right)
{
	if (!get_ongoing(phi))
		return (false);
	while (!get_fork_availability(phi->forks[i_left]) && !get_fork_availability(phi->forks[i_right]))
	{
		usleep(30);
		move_time(phi->now, 30);
	}
	set_fork_status(phi->forks[i_left], true);
	set_fork_status(phi->forks[i_right], true);
	if (!print_activity(phi, MSG_FORK))
		return (false);
	if (phi->nb_philo == 1)
		return (false);
	return (true);
}

// bool	take_leftfork(t_phi *phi, int i_left, int i_right)
// {
// 	if (!get_ongoing(phi))
// 		return (false);
// 	set_fork_status(phi->forks[i_left], true);
// 	if (!print_activity(phi, MSG_FORK))
// 		return (false);
// 	if (phi->nb_philo == 1)
// 		return (false);
// 	while (!get_fork_availability(phi->forks[i_right]))
// 	{
// 		usleep(30);
// 		move_time(phi->now, 30);
// 	}
// 	return (true);
// }

// bool	take_rightfork(t_phi *phi, int i_right)
// {
// 	if (!get_ongoing(phi))
// 		return (false);
// 	set_fork_status(phi->forks[i_right], true);
// 	if (!print_activity(phi, MSG_FORK))
// 		return (false);
// 	return (true);
// }

bool	eat(t_phi *phi, int i_left, int i_right)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_EAT))
		return (false);
	set_nb_meal_plus(phi->nb_meals);
	update_last_meal(phi);
	set_fork_status(phi->forks[i_left], false);
	set_fork_status(phi->forks[i_right], false);
	usleep(phi->time_to_eat * 1000);
	move_time(phi->now, phi->time_to_eat);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_SLEEP))
		return (false);
	usleep(phi->time_to_sleep * 1000);
	move_time(phi->now, phi->time_to_sleep);
	return (true);
}
