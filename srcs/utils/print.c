/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:31:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/15 12:56:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterr(char *s)
{
	write(STDERR_FILENO, P_RED, 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, P_NOC, 7);
}

char *get_color(int i)
{
	char *codes[6];

	codes[0] = P_LRED;
	codes[1] = P_GREEN;
	codes[2] = P_YELLOW;
	codes[3] = P_BLUE;
	codes[4] = P_PINK;
	codes[5] = P_TEAL;
	return (codes[i % 6]);
}

int		get_elapsed_time_ms(t_time *start, t_time *to)
{
	int	msec_start;
	int	msec_to;

	msec_start = start->tv_sec * 1000 + start->tv_usec / 1000;
	msec_to = to->tv_sec * 1000 + to->tv_usec / 1000;
	return (msec_to - msec_start);
}
