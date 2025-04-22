/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/22 21:33:10 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_mutex	*init_fork(void)
{
	t_mutex	*fork;

	fork = malloc(1 * sizeof(t_mutex));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(fork, NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

t_phi	*new_philo(t_data data)
{
	t_phi	*philo;

	philo = malloc(1 * sizeof(t_phi));
	if (!philo)
		return (NULL);
	philo->nb_meals = init_nb_meals();
	philo->timedie = init_timedie(data.time_to_die);
	if (!philo->nb_meals || !philo->timedie)
		return (free_phil(philo));
	philo->thread_id = 0;
	philo->time_to_die = data.time_to_die;
	philo->time_to_eat = data.time_to_eat;
	philo->time_to_sleep = data.time_to_sleep;
	philo->min_nb_meals = data.min_nb_meals;
	philo->ongoing = data.ongoing;
	philo->nb_philo = data.nb_philo;
	philo->forks = data.forks;
	philo->alive = data.alive;
	philo->now = malloc(sizeof(t_time));
	philo->debug = data.debug;
	return (philo);
}

int	create_philosophers(t_data *data)
{
	int		i;
	t_phi	*philo;

	data->philosophers = malloc((data->nb_philo + 1) * sizeof(t_phi));
	if (!data->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo + 1)
		data->philosophers[i++] = NULL;
	i = 0;
	while (i < data->nb_philo)
	{
		philo = new_philo(*data);
		if (!philo)
		{
			free_philos(data->philosophers);
			return (EXIT_FAILURE);
		}
		philo->index = i;
		data->philosophers[i] = philo;
		i++;
	}
	data->philosophers[i] = NULL;
	return (EXIT_SUCCESS);
}

int	create_forks(t_data *data)
{
	int		i;
	t_mutex	*fork;

	data->forks = malloc((data->nb_philo + 1) * sizeof(t_mutex));
	if (!data->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo + 1)
		data->forks[i++] = NULL;
	i = 0;
	while (i < data->nb_philo)
	{
		fork = init_fork();
		if (!fork)
		{
			free_forks(data->forks);
			return (EXIT_FAILURE);
		}
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
	fill_args(data, ac, av);
	data->threads = malloc(data->nb_philo * sizeof(pthread_t));
	data->ongoing = init_ongoing();
	data->alive = init_alive();
	if (!data->threads || !data->ongoing || !data->alive)
		return (false);
	if (create_forks(data) == EXIT_FAILURE)
		return (false);
	if (create_philosophers(data) == EXIT_FAILURE)
		return (false);
	return (true);
}
