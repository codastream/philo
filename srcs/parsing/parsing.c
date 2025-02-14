/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/26 18:49:45 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phi	*get_philo_at_index(t_data *data, int index)
{
	t_phi	*current;

	current = data->philosophers;
	if (index < 0 || index >= data->nb_philo)
		return (NULL);
	while (current)
	{
		if (current->index == index)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_phi	*get_first_philo(t_data *data)
{
	return (get_philo_at_index(data, 0));
}

t_phi	*get_last_philo(t_data *data)
{
	t_phi *current;

	current = data->philosophers;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

t_has_fork	*create_fork(t_data *data)
{
	t_has_fork *fork;

	fork = malloc(1 * sizeof(t_has_fork));
	check_malloc(data, fork);
	fork->has_fork = pthread_mutex_init(&fork->has_fork_m, NULL);
	return (fork);
}

t_nb_meals *create_nb_meals(t_data *data)
{
	t_nb_meals *nb_meals;

	nb_meals = malloc(1 * sizeof(t_nb_meals));
	check_malloc(data, nb_meals);
	nb_meals->nb_meals = pthread_mutex_init(&nb_meals->nb_meals_m, NULL);
	return (nb_meals);
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
	philo->left_fork = create_fork(data);
	philo->right_fork = create_fork(data);
	philo->nb_meals = create_nb_meals(data);
	philo->prev = NULL;
	philo->next = NULL;
	return (philo);
}

void	add_philosopher(t_data *data, int index)
{
	t_phi	*philo;

	philo = new_philo(data);
	check_malloc(data, philo);
	philo->index = index;
	if (index > 0)
	{
		philo->prev = get_last_philo(data);
		philo->prev->next = philo;
	}
}

void	create_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc((data->nb_philo) * sizeof(t_phi));
	check_malloc(data, data->philosophers);
	i = 0;
	while (i < data->nb_philo)
	{
		add_philosopher(data, i);
		i++;
	}
	if (data->nb_philo == 1) // necessary ?
	{
		data->philosophers->next = data->philosophers;
		data->philosophers->prev = data->philosophers;
	}
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
	else
		data->min_nb_meals = UNSET;
	create_philosophers(data);
}
