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

bool	check_all_alive(t_phi *phi)
{
	bool	all_alive;

	pthread_mutex_lock(&phi->check->check_m);
	all_alive = phi->check->all_alive;
	// printf("%sall are alive ? %d %s\n", P_GREEN, all_alive, P_NOC);
	pthread_mutex_unlock(&phi->check->check_m);
	return (all_alive);
}

void	update_fork_status(t_fork *fork, bool is_taken)
{
	pthread_mutex_lock(&fork->fork_m);
	fork->is_taken = is_taken;
	// if (is_taken)
	// 	printf("fork %d is now taken\n", fork->index);
	// else
	// 	printf("fork %d is now free\n", fork->index);
	pthread_mutex_unlock(&fork->fork_m);
}

bool	is_available_fork(t_fork *fork)
{
	bool	is_taken;

	pthread_mutex_lock(&fork->fork_m);
	is_taken = fork->is_taken;
	pthread_mutex_unlock(&fork->fork_m);
	return (!is_taken);
}

bool	print_activity(t_phi *phi, char *msg)
{
	int		ms;
	int		code;
	bool	can_print;

	// can_print = check_all_alive(phi);
	// if (!can_print)
	// 	return (false);
	can_print = check_all_alive(phi);
	if (can_print || !ft_strcmp(msg, MSG_DIED))
	{
		pthread_mutex_lock(&phi->print->print_m);
		code = gettimeofday(phi->now, NULL);
		if (code != 0)
		{
			pthread_mutex_unlock(&phi->check->check_m);
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

bool	check_time_to_die(t_phi *phi, bool *should_die)
{
	int	msec_now;
	int	msec_death;

	save_time(phi->now);
	msec_now = phi->now->tv_sec * 1000 + phi->now->tv_usec / 1000;
	msec_death = phi->last_meal + phi->time_to_die;
	if (phi->debug)
	{
		printf("%schecking time for phi # %d\nlast meal %d\ntime to die %d\nnow %d\nmsec death %d\n%s", P_BLUE, phi->index,  phi->last_meal, phi->time_to_die, msec_now, msec_death, P_NOC);
	}
	if (phi->min_nb_meals == UNSET)
		*should_die = msec_now >= msec_death;
	else
		*should_die = msec_now >= msec_death && phi->nb_meals->count >= phi->min_nb_meals;
	if (*should_die)
		return (true);
	else
		return (false);
}

void	update_last_meal(t_phi *phi)
{
	int	msec_now;

	save_time(phi->now);
	msec_now = phi->now->tv_sec * 1000 + phi->now->tv_usec / 1000;
	phi->last_meal = msec_now;
}

bool	think(t_phi *phi, int i_left, bool *all_alive)
{
	bool	code;

	code = print_activity(phi, "is thinking\t\t🧠\n");
	if (code == false)
	{
		*all_alive = false;
		return (false);
	}
	while (!is_available_fork(phi->forks[i_left]))
		usleep(60);
	return (true);
}

bool	take_leftfork(t_phi *phi, int i_left, int i_right)
{
	update_fork_status(phi->forks[i_left], true);
	if (!print_activity(phi, "has taken a fork\t🍴\n"))
		return (false);
	while (!is_available_fork(phi->forks[i_right]))
		usleep(60);
	return (true);
}

bool	take_rightfork(t_phi *phi, int i_right)
{
	update_fork_status(phi->forks[i_right], true);
	if (!print_activity(phi, "has taken a fork\t🍴\n"))
		return (false);
	return (true);
}

bool	eat(t_phi *phi, int i_left, int i_right)
{
	if (!print_activity(phi, "is eating\t\t🍝\n"))
		return (false);
	update_last_meal(phi);
	update_fork_status(phi->forks[i_left], false);
	update_fork_status(phi->forks[i_right], false);
	usleep(phi->time_to_eat * 1000);
	return (true);
}

bool	gosleep(t_phi *phi)
{
	if (!print_activity(phi, "is sleeping\t\t💤\n"))
		return (false);
	usleep(phi->time_to_sleep * 1000);
	return (true);
}

void	*routine(void *philo)
{
	t_phi	*phi;
	int		i_left;
	int		i_right;
	bool	all_alive;

	printf("in routine\n");
	phi = (t_phi *)philo;
	if (phi->index % 2 != 0)
		usleep(phi->time_to_eat * 1000);
	i_left = phi->index;
	i_right = phi->index + 1;
	if (phi->nb_philo == phi->index + 1)
		i_right = 0;
	if (phi->debug)
		printf("i left is %d right is %d\n", i_left, i_right);
	all_alive = true;
	while (all_alive)
	{
		if (!think(phi, i_left, &all_alive))
			break ;
		if (!take_leftfork(phi, i_left, i_right))
			break ;
		if (!take_rightfork(phi, i_right))
			break ;
		if (!eat(phi, i_left, i_right))
			break ;
		if (!gosleep(phi))
			break ;
	}
	return (NULL);
}

void	announce_end(t_data *data)
{
	pthread_mutex_lock(&data->check->check_m);
	data->check->all_alive = false;
	pthread_mutex_unlock(&data->check->check_m);
}

void	*monitor(void *dat)
{
	t_data	*data;
	t_phi	*phi;
	int		i;
	bool	all_alive;
	int		elapsed;

	data = (t_data *)dat;
	i = 0;
	all_alive = true;
	printf("in monitor\n");
	while (all_alive)
	{
		phi = data->philosophers[i];
		save_time(phi->now);
		elapsed = get_elapsed_meal_ms(phi->last_meal, phi->now);
		// printf("elapsed since last meal = %d\n", elapsed);
		if (elapsed > phi->time_to_die)
		{
			pthread_mutex_lock(&data->check->check_m);
			data->check->all_alive = false;
			pthread_mutex_unlock(&data->check->check_m);
			print_activity(phi, MSG_DIED);
		}
		if (i < data->nb_philo - 1)
			i++;
		else
			i = 0;
		pthread_mutex_lock(&phi->check->check_m);
		all_alive = phi->check->all_alive;
		pthread_mutex_unlock(&phi->check->check_m);
		if (phi->debug)
			printf("%sall alive ? - %d%s\n", P_BLUE, all_alive, P_NOC);
		usleep(60);
	}
	printf("%send of monitor%s\n", P_LPINK, P_NOC);
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
		printf("starting thread for %d\n", i);
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

void	save_time(t_time *time)
{
	int		code;

	code = gettimeofday(time, NULL);
	if (code != 0)
		return ;
}

