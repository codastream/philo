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
	int	nb_meals;

	nb_meals = get_nb_meal(phi);
	if (nb_meals % 2 == 0)
		dispatch_forks(phi, phi->index, phi->index + 1);
	else
		dispatch_forks(phi, phi->index + 1, phi->index);
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
	update_last_meal(phi);
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
