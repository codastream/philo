/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:32:18 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 19:57:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_death(t_alive *alive)
{
	pthread_mutex_lock(&alive->alive_m);
	alive->all_alive = false;
	pthread_mutex_unlock(&alive->alive_m);
}
