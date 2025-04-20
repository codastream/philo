/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 16:55:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_phi	*new_philo(t_data *data)
{
	t_phi	*philo;

	philo = malloc(1 * sizeof(t_phi));
	if (!philo)
		check_malloc(data, philo);
	philo->thread_id = 0;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->min_nb_meals = data->min_nb_meals;
	philo->nb_meals = 0;
	philo->nb_philo = data->nb_philo;
	philo->now = malloc(sizeof(t_time));
	return (philo);
}

void	create_philosophers(t_data *data)
{
	int		i;
	t_phi	*philo;

	data->philosophers = malloc((data->nb_philo) * sizeof(t_phi));
	check_malloc(data, data->philosophers);
	i = 0;
	while (i < data->nb_philo)
	{
		philo = new_philo(data);
		check_malloc(data, philo);
		philo->index = i;
		data->philosophers[i] = philo;
		i++;
	}
}

bool	parse_args(t_data *data, int ac, char **av)
{
	if (ac < 4 || ac > 6)
		return (false);
	data->start = malloc(1 * sizeof(t_time));
	if (!data->start)
		return (false);
	data->nb_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->min_nb_meals = UNSET;
	if (ac >= 5)
		data->min_nb_meals = ft_atoi(av[4]);
	data->debug = false;
	if (ac == 6)
		data->debug = true;
	data->philo_pids = malloc(data->nb_philo * sizeof(int));
	if (!data->philo_pids)
		return (false);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (false);
	data->activities = malloc(4 * sizeof(t_activity));
	if (!data->activities)
		return (false);
	create_philosophers(data);
	return (true);
}
