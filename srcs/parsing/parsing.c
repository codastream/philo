/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/24 16:07:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philosopher(t_data *data, int index)
{
	t_phi	*philo;

	philo = malloc(1 * sizeof(t_phi));
	if (!philo)
		check_malloc(data, philo);
	philo->index = index;
	philo->last_meal = 0;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->nb_meals = 0;
	philo->thread_id = 0;
	philo->fork_nb = pthread_mutex_init(&philo->fork_nb_m, NULL);
	if (philo->fork_nb != 0)
		clean(data);
	data->philosophers[index] = philo;
}

void	create_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc((data->nb_philo + 1) * sizeof(t_phi *));
	check_malloc(data, data->philosophers);
	i = 0;
	while (i < data->nb_philo)
	{
		create_philosopher(data, i);
		i++;
	}
	data->philosophers[i] = NULL;
}

void	parse_args(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
	{
		data->min_nb_meals = ft_atoi(av[4]);
	}
	create_philosophers(data);
}
