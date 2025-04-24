/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:00:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/24 23:03:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*get_fork(t_phi *phi, bool is_first)
{
	int		nb_meals;
	bool	even_i;
	bool	even_phi;

	nb_meals = get_nb_meal(phi);
	even_phi = phi->nb_philo % 2 == 0;
	even_i = phi->index % 2 == 0;
	if (is_first)
	{
		if (even_i)
			return (phi->forks[(phi->index + 1) % phi->nb_philo]);
		else
			return (phi->forks[phi->index]);
		if (!even_phi && phi->index + 1 == phi->nb_philo)
			return (phi->forks[(phi->index + 1) % phi->nb_philo]);
	}
	else
	{
		if (even_i)
			return (phi->forks[phi->index]);
		else
			return (phi->forks[(phi->index + 1) % phi->nb_philo]);
		if (!even_phi && phi->index + 1 == phi->nb_philo)
			return (phi->forks[phi->index]);
	}
}
