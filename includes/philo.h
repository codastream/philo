/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 14:45:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>	// memset
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write
# include <sys/time.h>	// gettimeofday
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include "colors.h"

# define UNSET -1
# define MSG_THINK "is thinking\n"
# define MSG_FORK "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_DIED "died\n"
# define MSG_USAGE "usage: philo\n<number_of_philosophers>\n\
	<time_to_die>\n<time_to_eat>\n<time_to_sleep>\n\
	[number_of_times_each_philosopher_must_eat]\n"

typedef pthread_mutex_t	t_mutex;

typedef enum e_act
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING
}	t_act;

typedef struct s_fork
{
	bool	is_taken;
	t_mutex	fork_m;
	int		index;
}	t_fork;
typedef struct s_nb_meals
{
	int		count;
	t_mutex	nb_meals_m;
}	t_nb_meals;

typedef struct s_print
{
	bool	can_print;
	t_mutex	print_m;
}	t_print;

typedef struct s_last_meal
{
	int		last_meal;
	t_mutex	last_meal_m;
}	t_last_meal;

typedef struct s_ongoing
{
	bool	is_ongoing;
	t_mutex	ongoing_m;
}	t_ongoing;

typedef struct s_alive
{
	bool	all_alive;
	t_mutex	alive_m;
}	t_alive;

typedef struct timeval	t_time;

typedef struct s_phi
{
	pthread_t		thread_id;
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_nb_meals;
	int				nb_philo;
	bool			debug;
	t_time			*start;
	t_time			*now;
	t_nb_meals		*nb_meals;
	t_fork			**forks;
	t_print			*print;
	t_ongoing		*ongoing;
	t_alive			*alive;
	t_last_meal		*last_meal;
}	t_phi;

typedef struct s_data
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_philo;
	int			min_nb_meals;
	pthread_t	*threads;
	pthread_t	monitor;
	t_print		*print;
	t_ongoing	*ongoing;
	t_alive		*alive;
	t_time		*start;
	t_phi		**philosophers;
	t_fork		**forks;
	bool		is_end;
	bool		debug;
}	t_data;

// checking
bool		check_args(int ac, char **av);

// parsing
void		add_philosopher(t_data *data, int index);
bool		parse_args(t_data *data, int ac, char **av);

// init
t_nb_meals	*init_nb_meals(t_data *data);
t_print		*init_print(t_data *data);
t_alive		*init_alive(t_data *data);
t_ongoing	*init_ongoing(t_data *data);
t_last_meal	*init_last_meal(t_phi *phi);

// mutex set
void		set_fork_status(t_fork *fork, bool is_taken);
void		set_is_ongoing(t_ongoing *ongoing, bool is_ongoing);
void		set_nb_meal_plus(t_nb_meals *meals);
void		update_last_meal(t_phi *phi);
void		set_death(t_alive *alive);

// mutex get
bool		get_fork_availability(t_fork *fork);
int			get_nb_meal(t_phi *phi);
bool		get_ongoing(t_phi *phi);
bool		get_all_alive(t_alive *alive);
int			get_last_meal(t_phi *phi);

// errors
void		check_malloc(t_data *data, void *allocated);
void		handle_error(t_data *data, char *msg);
void		clean(t_data *data);

// util strings
int			ft_strlen(char *s);
bool		is_digit(char c);
int			ft_strcmp(char *s1, char *s2);

// util conversion
long		ft_atol(const char *nb);
int			ft_atoi(const char *nb);
char		*ft_itoa(int n);

// util print
void		ft_puterr(char *s);

// util mem
void		ft_free_2d_char_null_ended(char **tab);
char		*ft_strcpy(char *dest, const char *src, size_t n);

// util time
int			save_time(t_time *time);
int			get_elapsed_time_ms(t_time *start, t_time *to);
int			get_elapsed_meal_ms(int last_meal, t_time *now);
char		*get_color(int i);
int			get_time_ms(t_time *time);
void		move_time(t_time *time, int ms);

// routines
void		live_love_pray(t_data *data);
bool		get_ongoing(t_phi *phi);
bool		print_activity(t_phi *phi, char *msg);

// monitor
void		*monitor(void *dat);
bool		have_all_eaten_enough(t_data *data);

// activity
bool		think(t_phi *phi, int i_left);
bool		try_take_forks(t_phi *phi, int i_left, int i_right);
bool		eat(t_phi *phi, int i_left, int i_right);
bool		gosleep(t_phi *phi);

// debug
void		print_philo(t_phi *phi);

#endif
