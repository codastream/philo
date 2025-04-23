/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:36 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 23:45:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	save_time(t_time *time)
{
	int		code;

	code = gettimeofday(time, NULL);
	if (code != 0)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	get_elapsed_meal_ms(int last_meal, t_time *now)
{
	int	msec_now;

	save_time(now);
	msec_now = now->tv_sec * 1000 + now->tv_usec / 1000;
	return (msec_now - last_meal);
}

int	get_elapsed_time_ms(t_time *start, t_time *to)
{
	int	msec_start;
	int	msec_to;

	msec_start = start->tv_sec * 1000 + start->tv_usec / 1000;
	msec_to = to->tv_sec * 1000 + to->tv_usec / 1000;
	return (msec_to - msec_start);
}

void	move_time(t_time *time, int ms)
{
	int	sec;
	int	usec;

	sec = ms / 1000;
	usec = ms * 1000;
	time->tv_sec += sec;
	time->tv_usec += usec;
}

long long	get_time_us(t_time *time)
{
	return (time->tv_sec * 1000000 + time->tv_usec);
}

int	get_time_ms(t_time *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}
