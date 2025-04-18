/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:21:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 22:28:18 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_data *data)
{
	t_phi	*philo;
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philosophers[i];
		free(philo->nb_meals);
		free(philo->last_meal);
		free(philo->now);
		free(philo);
		i++;
	}
	free(data->philosophers);
}

void	free_forks(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		free(data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	clean(t_data *data)
{
	if (data->philosophers)
		free_philo(data);
	if (data->forks)
		free_forks(data);
	free(data->alive);
	free(data->ongoing);
	free(data->print);
	free(data->start);
	free(data->threads);
	free(data);
}

void	check_malloc(t_data *data, void *allocated)
{
	if (!allocated)
		handle_error(data, "Memory allocation error\n");
}

void	handle_error(t_data *data, char *msg)
{
	ft_puterr(msg);
	clean(data);
}
