/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/05 17:35:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> // memset
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write
# include <sys/time.h> // gettimeofday
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include "colors.h"

# define UNSET -1

typedef pthread_mutex_t	t_mutex;

typedef enum	e_act
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING
}	t_act;

// typedef struct s_nb_forks
// {
// 	int		count;
// 	t_mutex	nb_forks_m;
// }	t_nb_forks;

typedef struct s_fork
{
	bool	is_taken;
	t_mutex	fork_m;
}	t_fork;
typedef struct s_nb_meals
{
	int		count;
	t_mutex	nb_meals_m;
}	t_nb_meals;

typedef struct timeval t_time;

typedef struct s_phi
{
	pthread_t		thread_id;
	int				index;
	int				time_to_die; // same in data
	int				time_to_eat; // same in data
	int				time_to_sleep; // same in data
	int				min_nb_meals; // same in data
	int				last_meal;
	int				nb_philo;
	t_time			*start;
	t_time			*print_time;
	t_nb_meals		*nb_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mutex			*print_m;
	t_fork			**forks;
	// t_nb_forks		*nb_forks;
}	t_phi;


typedef struct s_data
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_philo;
	int		min_nb_meals;
	t_time	*start;
	t_phi	**philosophers;
	t_fork	**forks;
}	t_data;

// checking
bool	check_args(int	ac, char **av);

// parsing
void	add_philosopher(t_data *data, int index);
void	parse_args(t_data *data, int ac, char **av);

// errors
void	check_malloc(t_data *data, void *allocated);
void	handle_error(t_data *data, char *msg);
void	clean(t_data *data);

// util strings
int		ft_strlen(char *s);
bool	is_digit(char c);

// util conversion
long	ft_atol(const char *nb);
int		ft_atoi(const char *nb);

// util print
void	ft_puterr(char *s);

// util mem
void	ft_free_2d_char_null_ended(char **tab);

// routines
void	save_start(t_data *data);

#endif
