/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:05:42 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/24 23:08:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	save_time(time);
	if (gettimeofday(time, NULL) == -1)
	{
		return (0);
	}
	ms = get_time_ms(time);
	return (ms);
}

void	ft_sleep(t_phi *phi, int ms)
{
	long	spent;

	spent = 0;
	while (spent < ms * 1000)
	{
		if (phi->time_death <= get_current_time_ms())
		{
			break ;
		}
		save_time(phi->now);
		spent += 150;
		usleep(150);
	}
}
