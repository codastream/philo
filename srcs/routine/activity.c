/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 19:35:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	think(t_phi *phi, int i_left)
{
	bool	code;

	code = print_activity(phi, "is thinking\t\t🧠\n");
	if (code == false)
	{
		return (false);
	}
	while (!get_fork_availability(phi->forks[i_left]))
		usleep(60);
	return (true);
}

bool	take_leftfork(t_phi *phi, int i_left, int i_right)
{
	set_fork_status(phi->forks[i_left], true);
	if (!print_activity(phi, "has taken a fork\t🍴\n"))
		return (false);
	while (!get_fork_availability(phi->forks[i_right]))
		usleep(60);
	return (true);
}

bool	take_rightfork(t_phi *phi, int i_right)
{
	set_fork_status(phi->forks[i_right], true);
	if (!print_activity(phi, "has taken a fork\t🍴\n"))
		return (false);
	return (true);
}

bool	eat(t_phi *phi, int i_left, int i_right)
{
	if (!print_activity(phi, "is eating\t\t🍝\n"))
		return (false);
	set_nb_meal_plus(phi->nb_meals);
	update_last_meal(phi);
	set_fork_status(phi->forks[i_left], false);
	set_fork_status(phi->forks[i_right], false);
	usleep(phi->time_to_eat * 1000);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!print_activity(phi, "is sleeping\t\t💤\n"))
		return (false);
	usleep(phi->time_to_sleep * 1000);
	return (true);
}
