/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/15 13:18:16 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// t_nb_forks	*init_nb_forks(t_data *data)
// {
// 	t_nb_forks *nb_forks;

// 	nb_forks = malloc(1 * sizeof(t_nb_forks));
// 	check_malloc(data, nb_forks);
// 	nb_forks->count = pthread_mutex_init(&nb_forks->nb_forks_m, NULL);
// 	return (fork);
// }

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

t_nb_meals *init_nb_meals(t_data *data)
{
	t_nb_meals *nb_meals;

	nb_meals = malloc(1 * sizeof(t_nb_meals));
	check_malloc(data, nb_meals);
	if (pthread_mutex_init(&nb_meals->nb_meals_m, NULL) != 0)
	{
		free(nb_meals);
		return (NULL);
	}
	nb_meals->count = 0;
	return (nb_meals);
}

t_print	*init_print(t_data *data)
{
	t_print	*print;

	print = malloc(1 *sizeof(t_print));
	check_malloc(data, print);
	if (pthread_mutex_init(&print->print_m, NULL) != 0)
	{
		free(print);
		return (NULL);
	}
	print->can_print = true;
	return (print);
}

t_phi *new_philo(t_data *data)
{
	t_phi	*philo;

	philo = malloc(1 * sizeof(t_phi));
	if (!philo)
		check_malloc(data, philo);
	philo->thread_id = 0;
	philo->last_meal = 0;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	// philo->nb_forks = init_nb_forks(data);
	philo->nb_meals = init_nb_meals(data);
	philo->print = data->print;
	philo->nb_philo = data->nb_philo;
	philo->forks = data->forks;
	philo->print_time = malloc(sizeof(t_time));
	philo->debug = data->debug;
	return (philo);
}

void	create_philosophers(t_data *data)
{
	int	i;
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
	int	i;
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
	if (ac >= 5)
	data->min_nb_meals = ft_atoi(av[4]);
	else
	data->min_nb_meals = UNSET;
	data->debug = false;
	if (ac == 6)
	data->debug = true;
	data->threads = malloc(data->nb_philo * sizeof(pthread_t));
	if (!data->threads)
	return (false);
	data->print = init_print(data);
	create_forks(data);
	create_philosophers(data);
	return (true);
}
