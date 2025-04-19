/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:31:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 11:41:42 by fpetit           ###   ########.fr       */
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


