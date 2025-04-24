/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:22:25 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/17 17:20: by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	solo(t_phi *phi)
{
	pthread_mutex_lock(phi->forks[0]);
	if (!print_activity(phi, MSG_FORK))
		return ;
	usleep(phi->time_to_die * 1000);
}

void	many(t_phi *phi)
{
	bool	is_ongoing;

	is_ongoing = true;
	while (is_ongoing)
	{
		if (!eat(phi))
			break ;
		if (!gosleep(phi))
			break ;
		if (!think(phi))
			break ;
		is_ongoing = get_ongoing(phi);
	}
}

t_mutex	*get_fork(t_phi *phi, bool is_first)
{
	int		nb_meals;
	int		index;
	bool	even_meal;
	bool	even_i;
	bool	even_phi;

	index = phi->index;
	nb_meals = get_nb_meal(phi);
	even_phi = phi->nb_philo % 2 == 0;
	even_meal = nb_meals % 2 == 0;
	even_i = phi->index % 2 == 0;
	if (is_first)
	{
		if (even_i && index + 1 == phi->nb_philo)
			return (phi->forks[index]);
		else
			return (phi->forks[(index + 1) % phi->nb_philo]);
	}
	else
	{
		if (even_i && index + 1 == phi->nb_philo)
			return (phi->forks[(index + 1) % phi->nb_philo]);
		else
			return (phi->forks[index]);
	}
}

void	*routine(void *philo)
{
	t_phi	*phi;

	phi = (t_phi *)philo;
	if (phi->nb_philo == 1)
	{
		solo(phi);
		return (NULL);
	}
	many(phi);
	printf("after many for phi %d\n", phi->index);
	return (NULL);
}

void	live_love_pray(t_data *data)
{
	int			i;
	t_phi		*phi;
	pthread_t	thread;

	i = 0;
	save_time(data->start);
	while (i < data->nb_philo)
	{
		phi = data->philosophers[i];
		phi->start = data->start;
		save_time(phi->now);
		phi->time_death = get_time_ms(phi->now) + phi->time_to_die;
		phi->last_meal = init_last_meal(phi);
		pthread_create(&thread, NULL, routine, phi);
		data->threads[i++] = thread;
	}
	pthread_create(&thread, NULL, monitor, data);
	data->monitor = thread;
	i = 0;
	while (i < data->nb_philo)
	{
		thread = data->threads[i++];
		pthread_join(thread, NULL);
	}
	pthread_join(data->monitor, NULL);
}
