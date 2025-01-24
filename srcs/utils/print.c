/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:31:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/24 14:41:51 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterr(char *s)
{
	write(STDERR_FILENO, P_RED, 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, P_NOC, 7);
}
