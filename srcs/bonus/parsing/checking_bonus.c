/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/19 18:42:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_pos_atoi_string(char *s)
{
	int		num_size;
	long	ln;
	char	*l;

	l = s;
	while (*s == ' ' || *s == '\t')
		s++;
	if (s[0] == '-')
		return (false);
	while (*s == '0')
		s++;
	num_size = 0;
	while (is_digit(*s))
	{
		s++;
		num_size++;
	}
	if (num_size > 10)
		return (false);
	ln = ft_atol(l);
	if (ln > INT_MAX || ln < 1)
		return (false);
	return (true);
}

bool	check_args(int ac, char **av)
{
	int	i;
	int	int_arg_nb;

	i = 0;
	if (ac < 4 || ac > 6)
		return (false);
	int_arg_nb = ac;
	if (ac == 6)
		int_arg_nb = 5;
	while (i < int_arg_nb)
	{
		if (!is_pos_atoi_string(av[i]))
		{
			ft_puterr(MSG_VALID);
			return (false);
		}
		i++;
	}
	return (true);
}
