/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:44:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 17:39:32 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	skip_blanks(const char **str)
{
	while (**str && ((**str >= 9 && **str <= 13) || **str == 32))
		++*str;
}

static int	check_neg(const char **nptr)
{
	int	neg;

	neg = 1;
	if ((**nptr) == '+' || (**nptr) == '-')
	{
		if ((**nptr) == '-')
			neg *= -1;
		(*nptr)++;
	}
	return (neg);
}

int	ft_atoi(const char *nb)
{
	int			neg;
	long		result;

	skip_blanks(&nb);
	neg = check_neg(&nb);
	result = 0;
	while (is_digit(*nb))
	{
		result *= 10;
		result += (*nb - '0');
		nb++;
	}
	return ((int)(neg * result));
}

long	ft_atol(const char *nb)
{
	int			neg;
	long long	result;

	skip_blanks(&nb);
	neg = check_neg(&nb);
	result = 0;
	while (is_digit(*nb))
	{
		result *= 10;
		result += (*nb - '0');
		nb++;
	}
	return ((long)(neg * result));
}
