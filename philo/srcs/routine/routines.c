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
	ft_sleep(-1, phi);
}

void	many(t_phi *phi)
{
	bool	is_ongoing;

	is_ongoing = true;
	while (is_ongoing)
	{
		if (!try_take_forks(phi))
			break ;
		if (!eat(phi))
			break ;
		if (!gosleep(phi))
			break ;
		if (!think(phi))
			break ;
		is_ongoing = get_ongoing(phi);
	}
}

void	dispatch_forks(t_phi *phi)
{
	if (phi->index % 2 != 0)
	{
		phi->fork1 = phi->forks[phi->index];
		phi->fork2 = phi->forks[phi->index + 1];
	}
	else
	{
		phi->fork1 = phi->forks[phi->index + 1];
		phi->fork2 = phi->forks[phi->index];
	}
	if (phi->nb_philo == phi->index + 1)
	{
		phi->fork1 = phi->forks[phi->index];
		phi->fork2 = phi->forks[0];
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
	dispatch_forks(phi);
	// if (phi->index % 2 != 0)
	// 	usleep((phi->time_to_eat - 1) * 1000);
	many(phi);
	return (NULL);
}

void	live_love_pray(t_data *data)
{
	int			i;
	t_phi		*philo;
	pthread_t	thread;

	i = 0;
	save_time(data->start);
	while (i < data->nb_philo)
	{
		philo = data->philosophers[i];
		philo->start = data->start;
		save_time(philo->now);
		philo->last_meal = init_last_meal(philo);
		pthread_create(&thread, NULL, routine, philo);
		data->threads[i++] = thread;
	}
	pthread_create(&thread, NULL, monitor, data);
	data->monitor = thread;
	i = 0;
	while (i < data->nb_philo)
	{
		thread = data->threads[i];
		pthread_join(thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
