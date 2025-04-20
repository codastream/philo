/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:22:25 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/17 17:20: by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*append_time_and_index(char *dest, char *mschar, int index, \
		char *indexchar)
{
	dest = ft_strcpy(dest, P_PINK, ft_strlen(P_PINK));
	dest = ft_strcpy(dest, "[", 1);
	dest = ft_strcpy(dest, mschar, ft_strlen(mschar));
	dest = ft_strcpy(dest, "] ", 2);
	dest = ft_strcpy(dest, get_color(index), ft_strlen(get_color(index)));
	dest = ft_strcpy(dest, "[", 1);
	dest = ft_strcpy(dest, indexchar, ft_strlen(indexchar));
	dest = ft_strcpy(dest, "] ", 2);
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
	size = ft_strlen(P_PINK) + 1 + ft_strlen(mschar) + 2 \
		+ ft_strlen(get_color(index)) + 1 + ft_strlen(indexchar) \
		+ 2 + ft_strlen(P_NOC) + ft_strlen(msg) + 1;
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
		if (!ft_strcmp(msg, MSG_FORK) && phi->nb_philo > 1)
			write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (true);
}

void	*routine(void *philo)
{
	t_phi	*phi;
	int		i_right;
	bool	is_ongoing;

	phi = (t_phi *)philo;
	if (phi->index % 2 != 0)
		usleep(phi->time_to_eat * 1000);
	i_right = phi->index + 1;
	if (phi->nb_philo == phi->index + 1)
		i_right = 0;
	is_ongoing = true;
	while (is_ongoing)
	{
		if (!think(phi, phi->index))
			break ;
		if (!try_take_forks(phi, phi->index, i_right))
			break ;
		if (!eat(phi, phi->index, i_right))
			break ;
		if (!gosleep(phi))
			break ;
		is_ongoing = get_ongoing(phi);
	}
	return (NULL);
}

void	live_love_pray(t_data *data)
{
	int			i;
	t_phi		*philo;
	pthread_t	thread;

	i = 0;
	save_time(data->start);
	while (i < data->nb_philo)
	{
		philo = data->philosophers[i];
		philo->start = data->start;
		save_time(philo->now);
		philo->last_meal = init_last_meal(philo);
		pthread_create(&thread, NULL, routine, philo);
		data->threads[i++] = thread;
	}
	pthread_create(&thread, NULL, monitor, data);
	data->monitor = thread;
	i = 0;
	while (i < data->nb_philo)
	{
		thread = data->threads[i];
		pthread_join(thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
