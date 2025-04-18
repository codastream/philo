/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 19:37:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	philo->print = data->print;
	philo->ongoing = data->ongoing;
	philo->nb_philo = data->nb_philo;
	philo->forks = data->forks;
	philo->alive = data->alive;
	philo->now = malloc(sizeof(t_time));
	philo->debug = data->debug;
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

void	create_forks(t_data *data)
{
	int		i;
	t_fork	*fork;

	data->forks = malloc(data->nb_philo * sizeof(t_fork));
	check_malloc(data, data->forks);
	i = 0;
	while (i < data->nb_philo)
	{
		fork = init_fork(data, i);
		data->forks[i] = fork;
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
	data->print = init_print(data);
	data->ongoing = init_ongoing(data);
	data->alive = init_alive(data);
	create_forks(data);
	create_philosophers(data);
	return (true);
}
