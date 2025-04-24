/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:21:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/24 23:07:44 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	think(t_phi *phi)
{
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_THINK))
		return (false);
	return (true);
}

bool	try_take_forks_and_eat(t_phi *phi)
{
	phi->fork1 = get_fork(phi, true);
	phi->fork2 = get_fork(phi, false);
	if (!get_ongoing(phi))
		return (false);
	pthread_mutex_lock(phi->fork1);
	if (!print_activity(phi, MSG_FORK))
	{
		pthread_mutex_unlock(phi->fork1);
		return (false);
	}
	pthread_mutex_lock(phi->fork2);
	if (!print_activity(phi, MSG_FORK) \
		|| !print_activity(phi, MSG_EAT))
	{
		pthread_mutex_unlock(phi->fork1);
		pthread_mutex_unlock(phi->fork2);
		return (false);
	}
	return (true);
}

bool	eat(t_phi *phi)
{
	int	start;
	int	ms;

	if (!try_take_forks_and_eat(phi))
		return (false);
	set_nb_meal_plus(phi->nb_meals);
	phi->time_death += phi->time_to_die;
	update_last_meal(phi);
	save_time(phi->now);
	start = get_time_ms(phi->now);
	ms = get_current_time_ms();
	while (ms < (start + phi->time_to_eat))
	{
		if (ms >= phi->time_death)
		{
			pthread_mutex_unlock(phi->fork2);
			pthread_mutex_unlock(phi->fork1);
			return (false);
		}
		usleep(150);
		ms = get_current_time_ms();
	}
	return (true);
}

bool	gosleep(t_phi *phi)
{
	int	ms;
	int	start;

	pthread_mutex_unlock(phi->fork2);
	pthread_mutex_unlock(phi->fork1);
	if (!get_ongoing(phi))
		return (false);
	if (!print_activity(phi, MSG_SLEEP))
		return (false);
	save_time(phi->now);
	start = get_time_ms(phi->now);
	ms = get_current_time_ms();
	while (ms < (start + phi->time_to_sleep + 1))
	{
		if (ms >= phi->time_death)
			return (false);
		usleep(150);
		ms = get_current_time_ms();
	}
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
