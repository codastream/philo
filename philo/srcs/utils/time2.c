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

long long	get_current_time_us(void)
{
	t_time		time;
	long long	us;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (0);
	}
	us = get_time_us(&time);
	return (us);
}

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

void	ft_sleep(int ms, t_phi *phi)
{
	// (void) phi;
	// usleep(ms * 1000);
	int		time_die_ms;
	int		current_ms;
	int		start_ms;
	int		spent;

	spent = 0;
	time_die_ms = get_timedie(phi->timedie);
	start_ms = get_now(phi->now);
	if (phi->debug)
		printf("phi %d time die %d stared sleeping at%d\n", phi->index, time_die_ms, start_ms);
	while (true)
	{
		current_ms = get_now(phi->now);
		spent = current_ms - start_ms; 
		if (time_die_ms < current_ms)
			break ;
		else if (spent < ms)
		{
			usleep(100);
		}
		else
			break ;
	}
}
