/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:43:55 by fpetit            #+#    #+#             */
/*   Updated: 2025/01/26 18:48:05 by fpetit           ###   ########.fr       */
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

typedef struct s_has_fork
{
	bool	has_fork;
	t_mutex	has_fork_m;
}	t_has_fork;

typedef struct s_nb_meals
{
	int		nb_meals;
	t_mutex	nb_meals_m;
}	t_nb_meals;

typedef struct s_phi t_phi;

typedef struct s_phi
{
	pthread_t		thread_id;
	int				index;
	int				time_to_die; // same in data
	int				time_to_eat; // same in data
	int				time_to_sleep; // same in data
	int				min_nb_meals; // same in data
	int				last_meal;
	t_nb_meals		*nb_meals;
	t_has_fork		*left_fork;
	t_has_fork		*right_fork;
	t_phi			*prev;
	t_phi			*next;
}	t_phi;

typedef struct s_data
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_philo;
	int		min_nb_meals;
	t_phi	*philosophers;
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

#endif
