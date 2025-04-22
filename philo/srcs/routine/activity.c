/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 21:43:51 by fpetit           ###   ########.fr       */
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

bool	try_take_forks(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	pthread_mutex_lock(phi->fork1);
	pthread_mutex_lock(phi->fork2);
	if (!print_activity(phi, MSG_FORK))
		return (false);
	if (!print_activity(phi, MSG_FORK))
		return (false);
	return (true);
}

bool	eat(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_EAT))
		return (false);
	set_nb_meal_plus(phi->nb_meals);
	update_last_meal(phi);
	save_time(phi->now);
	extend_time_to_die(phi->timedie, phi->time_to_eat);
	ft_sleep(phi->time_to_eat, phi);
	pthread_mutex_unlock(phi->fork2);
	pthread_mutex_unlock(phi->fork1);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_SLEEP))
		return (false);
	ft_sleep(phi->time_to_sleep, phi);
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
