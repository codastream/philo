/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 20:25:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_fork(t_data *data, int i)
{
	t_fork	*fork;

	fork = malloc(1 * sizeof(t_fork));
	check_malloc(data, fork);
	if (pthread_mutex_init(&fork->fork_m, NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	fork->is_taken = false;
	fork->index = i;
	return (fork);
}

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
	philo->nb_meals = init_nb_meals(data);
	philo->ongoing = data->ongoing;
	philo->nb_philo = data->nb_philo;
	philo->forks = data->forks;
	philo->alive = data->alive;
	philo->now = malloc(sizeof(t_time));
	philo->debug = data->debug;
	return (philo);
}

int	create_philosophers(t_data *data)
{
	int		i;
	t_phi	*philo;

	data->philosophers = malloc((data->nb_philo) * sizeof(t_phi));
	if (!data->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo)
	{
		philo = new_philo(data);
		check_malloc(data, philo);
		philo->index = i;
		data->philosophers[i] = philo;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_forks(t_data *data)
{
	int		i;
	t_fork	*fork;

	data->forks = malloc(data->nb_philo * sizeof(t_fork));
	if (!data->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo)
	{
		fork = init_fork(data, i);
		data->forks[i] = fork;
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	parse_args(t_data *data, int ac, char **av)
{
	if (ac < 4 || ac > 6)
		return (false);
	data->start = malloc(1 * sizeof(t_time));
	data->now = malloc(1 * sizeof(t_time));
	if (!data->start || !data->now)
		return (false);
	fill_args(&data, ac, av);
	data->threads = malloc(data->nb_philo * sizeof(pthread_t));
	data->ongoing = init_ongoing(data);
	data->alive = init_alive(data);
	if (!data->threads || !data->ongoing || data->alive)
		return (false);
	if (create_forks(data) == EXIT_FAILURE)
		return (false);
	if (create_philosophers(data) == EXIT_FAILURE)
		return (false);
	return (true);
}
