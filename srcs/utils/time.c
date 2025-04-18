/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:36 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 23:33:46 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_time(t_time *time)
{
	int		code;

	code = gettimeofday(time, NULL);
	if (code != 0)
		return ;
}

void	move_time(t_time *time, int ms)
{
	int	sec;
	int usec;

	sec = ms / 1000;
	usec = ms & 1000;
	time->tv_sec += sec;
	time->tv_usec += usec;
}

int	get_time_ms(t_time *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}
