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

bool	print_activity(t_phi *phi, char *msg)
{
	int		ms;
	int		code;
	bool	is_ongoing;

	is_ongoing = get_ongoing(phi);
	if (is_ongoing || !ft_strcmp(msg, MSG_DIED))
	{
		pthread_mutex_lock(&phi->print->print_m);
		code = gettimeofday(phi->now, NULL);
		if (code != 0)
		{
			pthread_mutex_unlock(&phi->print->print_m);
			return (false);
		}
		if (phi->debug)
		{
			printf("code is %d - time is %ld s %ld usec\n", code, phi->now->tv_sec, phi->now->tv_usec);
			printf("start time is %ld \n", phi->start->tv_usec);
		}
		ms = get_elapsed_time_ms(phi->start, phi->now);
		printf("%s%6d%s %d %s%s", P_PINK, ms, get_color(phi->index), phi->index, P_NOC, msg);
		pthread_mutex_unlock(&phi->print->print_m);
	}
	return (true);
}

void	*routine(void *philo)
{
	t_phi	*phi;
	int		i_left;
	int		i_right;
	bool	is_ongoing;

	phi = (t_phi *)philo;
	if (phi->index % 2 != 0)
		usleep(phi->time_to_eat * 1000);
	i_left = phi->index;
	i_right = phi->index + 1;
	if (phi->nb_philo == phi->index + 1)
		i_right = 0;
	if (phi->debug)
		printf("i left is %d right is %d\n", i_left, i_right);
	is_ongoing = true;
	while (is_ongoing)
	{
		if (!think(phi, i_left))
			break ;
		if (!take_leftfork(phi, i_left, i_right))
			break ;
		if (!take_rightfork(phi, i_right))
			break ;
		if (!eat(phi, i_left, i_right))
			break ;
		if (!gosleep(phi))
			break ;
		is_ongoing = get_ongoing(phi);
	}
	// printf("end of routine for %d\n", phi->index);
	return (NULL);
}

void	live_love_pray(t_data *data)
{
	int			i;
	t_phi		*philo;
	pthread_t	thread;

	i = 0;

	while (i < data->nb_philo)
	{
		philo = data->philosophers[i];
		philo->start = data->start;
		update_last_meal(philo);
		pthread_create(&thread, NULL, routine, philo);
		data->threads[i] = thread;
		i++;
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

