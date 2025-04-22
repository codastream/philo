/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:21:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 21:25:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_phi **philos)
{
	t_phi	*philo;
	int		i;

	i = 0;
	while (philos[i])
	{
		philo = philos[i];
		free(philo->nb_meals);
		free(philo->last_meal);
		free(philo->now);
		free(philo);
		i++;
	}
	free(philos);
}

void	free_forks(t_fork **forks)
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
		free_philo(data->philosophers);
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
