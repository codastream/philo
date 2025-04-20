/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:21:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 17:48:09 by fpetit           ###   ########.fr       */
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
		free(philo->now);
		free(philo);
		i++;
	}
	free(data->philosophers);
}

void	clean(t_data *data)
{
	if (data->philosophers)
		free_philo(data);
	if (data->forks)
		free(data->forks);
	if (data->start)
		free(data->start);
	if (data->threads)
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
