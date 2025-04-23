/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:03:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 23:16:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*append_time_and_index(char *dest, char *mschar, int index, \
		char *indexchar)
{
	dest = ft_strcpy(dest, P_PINK, ft_strlen(P_PINK));
	dest = ft_strcpy(dest, mschar, ft_strlen(mschar));
	dest = ft_strcpy(dest, " ", 1);
	dest = ft_strcpy(dest, get_color(index), ft_strlen(get_color(index)));
	dest = ft_strcpy(dest, indexchar, ft_strlen(indexchar));
	dest = ft_strcpy(dest, " ", 1);
	dest = ft_strcpy(dest, P_NOC, ft_strlen(P_NOC));
	return (dest);
}

char	*init_buffer(int ms, int index, char *msg)
{
	int		size;
	char	*buffer;
	char	*dest;
	char	*mschar;
	char	*indexchar;

	mschar = ft_itoa(ms);
	indexchar = ft_itoa(index);
	if (!mschar || !indexchar)
		return (NULL);
	size = ft_strlen(P_PINK) + 1 + ft_strlen(mschar) \
		+ ft_strlen(get_color(index)) + 1 + ft_strlen(indexchar) \
		+ ft_strlen(P_NOC) + ft_strlen(msg) + 1;
	buffer = malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	dest = buffer;
	dest = append_time_and_index(dest, mschar, index, indexchar);
	dest = ft_strcpy(dest, msg, ft_strlen(msg));
	*dest = '\0';
	free(mschar);
	free(indexchar);
	return (buffer);
}

bool	print_activity(t_phi *phi, char *msg)
{
	int		ms;
	bool	is_ongoing;
	char	*buffer;

	is_ongoing = get_all_alive(phi->alive) && get_ongoing(phi);
	if (is_ongoing)
	{
		save_time(phi->now);
		ms = get_elapsed_time_ms(phi->start, phi->now);
		buffer = init_buffer(ms, phi->index + 1, msg);
		write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (true);
}
