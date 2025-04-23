/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:05:42 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 23:44:19 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_current_time_ms(void)
{
	t_time	time;
	int		ms;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (0);
	}
	ms = get_time_ms(&time);
	return (ms);
}

int	get_now(t_time *time)
{
	int		ms;

	if (gettimeofday(time, NULL) == -1)
	{
		return (0);
	}
	ms = get_time_ms(time);
	return (ms);
}
