/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:23:24 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 23:16:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_2d_char_null_ended(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strcpy(char *dest, const char *src, size_t n)
{
	if (!src && !dest)
		return (NULL);
	while (n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	return (dest);
}
