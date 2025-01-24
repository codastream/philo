/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:31:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/24 14:15:18 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_digit(char c)
{
	bool	is_digit;

	is_digit = c >= '0' && c <= '9';
	return (is_digit);
}

int	ft_strlen(char *s)
{
	int	size;

	size = 0;
	while (s[size])
	{
		size++;
	}
	return (size);
}
