/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:21:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 21:24:00 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*free_phil(t_phi *philo)
{
	if (philo->nb_meals)
		free(philo->nb_meals);
	if (philo->last_meal)
		free(philo->last_meal);
	if (philo->now)
		free(philo->now);
	free(philo);
	return (NULL);
}

void	free_philos(t_phi **philos)
{
	int		i;

	i = 0;
	while (philos[i])
	{
		free_phil(philos[i]);
		i++;
	}
	free(philos);
}

void	free_forks(t_mutex **forks)
{
	int		i;

	i = 0;
	while (forks[i])
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	clean(t_data *data)
{
	if (data->philosophers)
		free_philos(data->philosophers);
	if (data->forks)
		free_forks(data->forks);
	if (data->alive)
		free(data->alive);
	if (data->ongoing)
		free(data->ongoing);
	if (data->start)
		free(data->start);
	if (data->now)
		free(data->now);
	if (data->threads)
		free(data->threads);
}
