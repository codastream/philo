/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:05:42 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 21:55:12 by fpetit           ###   ########.fr       */
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

void	ft_sleep(int ms, t_phi *phi)
{
	int		time_die_ms;
	int		spent;

	spent = 0;
	while (true)
	{
		time_die_ms = get_timedie(phi->timedie);
		if (time_die_ms < get_current_time_ms())
			break ;
		else if (ms <= 0 || (ms > 0 && spent < ms * 1000))
		{
			usleep(100);
			spent += 100;
		}
		else if (ms > 0 && spent * 1000 >= ms)
			break ;
	}
}
