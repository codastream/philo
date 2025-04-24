/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 23:33:18 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	think(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_THINK))
		return (false);
	return (true);
}

bool	eat(t_phi *phi)
{
	phi->fork1 = get_fork(phi, true);
	phi->fork2 = get_fork(phi, false);
	if (!get_ongoing(phi))
		return (false);
	pthread_mutex_lock(phi->fork1);
	if (!print_activity(phi, MSG_FORK))
		return (false);
	pthread_mutex_lock(phi->fork2);
	if (!print_activity(phi, MSG_FORK))
		return (false);
	if (!print_activity(phi, MSG_EAT))
		return (false);
	set_nb_meal_plus(phi->nb_meals);
	phi->time_death += phi->time_to_die;
	update_last_meal(phi);
	// ft_sleep(phi, phi->time_to_eat);
	usleep(phi->time_to_eat * 1000);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!get_ongoing(phi))
	return (false);
	pthread_mutex_unlock(phi->fork2);
	pthread_mutex_unlock(phi->fork1);
	if (!print_activity(phi, MSG_SLEEP))
		return (false);
	usleep(phi->time_to_sleep * 1000);
	usleep(500);
	// ft_sleep(phi, phi->time_to_sleep + 1);
	return (true);
}

bool	print_death(t_data *data, t_phi *phi, char *msg)
{
	int		ms;
	char	*buffer;

	if (!ft_strcmp(msg, MSG_DIED))
	{
		save_time(data->now);
		usleep(3);
		ms = get_elapsed_time_ms(phi->start, data->now);
		buffer = init_buffer(ms, phi->index + 1, msg);
		write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (true);
}
