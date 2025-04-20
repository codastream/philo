/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/20 16:59:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>	// memset
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write
# include <sys/time.h>	// gettimeofday
# include <semaphore.h> // sem_open, ...
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include "colors.h"

# define UNSET 0
# define MSG_THINK "is thinking\n"
# define MSG_FORK "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_DIED "died\n"
# define MSG_VALID "\033[1;31mplease enter a number between 1 \
and 2 147 483 647 included\033[0m\n"
# define MSG_USAGE "\033[1;31musage:\033[0m\n\033[0;34mphilo\033[0m \
<number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"

typedef pthread_mutex_t	t_mutex;

typedef enum e_act
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING
}	t_act;

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
	int				nb_meals;
	int				last_meal;
	t_time			*start;
	t_time			*now;
	bool			is_dead;
}	t_phi;

typedef void (*t_activity)(t_phi *);

typedef struct s_data
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_philo;
	int			min_nb_meals;
	int			*philo_pids;
	t_time		*start;
	t_phi		**philosophers;
	sem_t		*forks;
	t_activity	*activities;
	pthread_t	monitor;
	bool		is_end;
	bool		debug;
}	t_data;

// checking
bool		check_args(int ac, char **av);

// parsing
void		add_philosopher(t_data *data, int index);
bool		parse_args(t_data *data, int ac, char **av);

// meals
void		update_last_meal(t_phi *phi);
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
int			live_love_pray(t_data *data);
bool		print_activity(t_phi *phi, char *msg);

// monitor
void		*monitor(void *dat);
bool		have_all_eaten_enough(t_data *data);

// activity
bool		think(t_phi *phi);
bool		try_take_forks(t_phi *phi);
bool		eat(t_phi *phi);
bool		gosleep(t_phi *phi);

#endif
