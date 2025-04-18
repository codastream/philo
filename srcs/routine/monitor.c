/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:20:19 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/18 23:24:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	have_all_eaten_enough(t_data *data)
{
	int	i;
	int	enough;
	int	nb_meals;

	enough = data->min_nb_meals;
	if (data->debug)
		printf("checking if have eaten enough (== %d)\n", enough);
	if (enough == UNSET)
		return (true);
	i = 0;
	while (data->philosophers[i])
	{
		nb_meals = get_nb_meal(data->philosophers[i]);
		if (data->debug)
			printf("nb meals for #%d is %d\n", i, nb_meals);
		if (nb_meals < enough)
			return (false);
		i++;
	}
	return (true);
}

bool	is_alive(t_phi *phi)
{
	int	elapsed;
	int	last_meal;

	last_meal = get_last_meal(phi);
	elapsed = get_elapsed_meal_ms(last_meal, phi->now);
	if (elapsed > phi->time_to_die)
	{
		set_death(phi->alive);
		usleep(10);
		print_activity(phi, MSG_DIED);
		return (false);
	}
	return (true);
}

bool	check_all_phi(t_data *data, bool (*f) (t_phi *))
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (!f(data->philosophers[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_ongoing(t_data *data)
{
	bool	all_alive;
	bool	is_ongoing;

	all_alive = check_all_phi(data, is_alive);
	if (data->min_nb_meals == UNSET)
		is_ongoing = all_alive;
	else
		is_ongoing = all_alive && !have_all_eaten_enough(data);
	return (is_ongoing);
}

void	*monitor(void *dat)
{
	t_data	*data;
	t_phi	*phi;
	int		i;
	bool	is_ongoing;

	data = (t_data *)dat;
	i = 0;
	is_ongoing = true;
	if (data->debug)
		printf("in monitor\n");
	while (is_ongoing)
	{
		phi = data->philosophers[i];
		save_time(phi->now);
		is_ongoing = check_ongoing(data);
		set_is_ongoing(data->ongoing, is_ongoing);
		// if (elapsed > data->time_to_die)
		// 	print_activity(phi, MSG_DIED);
		if (i < data->nb_philo - 1)
			i++;
		else
			i = 0;
		// if (phi->debug)
		// printf("%songoing ? - %d%s\n", P_BLUE, is_ongoing, P_NOC);
		usleep(60);
	}
	// printf("end of monitor\n");
	return (NULL);
}
