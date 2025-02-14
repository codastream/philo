/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:21:33 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/26 18:50:56 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_phi *philo)
{
	t_phi	*tmp;

	while (philo)
	{
		tmp = philo->next;
		// pthread_mutex_destroy(&philo->left_fork->has_fork_m);
		// pthread_mutex_destroy(&philo->right_fork->has_fork_m);
		// pthread_mutex_destroy(&philo->nb_meals->nb_meals_m);
		free(philo->nb_meals);
		free(philo->left_fork);
		free(philo->right_fork);
		free(philo);
		philo = tmp;
	}
}

void	clean(t_data *data)
{
	if (data->philosophers)
		free_philo(data->philosophers);
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
