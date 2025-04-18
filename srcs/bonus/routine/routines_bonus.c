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

#include "philo_bonus.h"

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

	return (true);
}

void	do_activity(void *philo, t_act f)
{
	t_phi	*phi;

	f(phi);
	return (NULL);
}

int	live_love_pray(t_data *data)
{
	int			i;
	t_phi		*philo;
	pthread_t	thread;
	int			pid;
	bool		all_alive;
	int			act_i;
	t_act		f;

	i = 0;
	save_time(data->start);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		philo = data->philosophers[i];
		philo->start = data->start;
		save_time(philo->now);
		philo->last_meal = get_time_ms(philo->now);
		act_i = 0;
		while (all_alive)
		{
			pid = fork();
			if (pid == -1)
				return (EXIT_FAILURE);
			if (pid == 0)
			{

			}
			data->philo_pids[i] = pid;
		}
		i++;
	}
	pthread_create(&thread, NULL, monitor, data);
	data->monitor = thread;
	pthread_join(data->monitor, NULL);
	return (EXIT_SUCCESS);
}
