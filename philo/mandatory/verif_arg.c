/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:22:38 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/05 19:01:28 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_verif_max_int(char *s)
{
	long int	i;
	long int	reponse;

	i = 0;
	reponse = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		reponse = reponse * 10;
		reponse = reponse + s[i] - '0';
		if (reponse > 2147483647 || reponse < -2147483648)
		{
			ft_putendl_fd("Error : overflow detected", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_verif_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
			{
				ft_putendl_fd("Error : digit required", 2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_verif_nber_philo(char **av)
{
	int	tmp;

	tmp = ft_atoi(av[1]);
	if (ft_verif_max_int(av[1]) == -1)
		return (-1);
	if (tmp < 1)
	{
		ft_putendl_fd("Error : not enough of philosophers", 2);
		return (-1);
	}
	return (0);
}

int	ft_verif_time_to(char **av)
{
	int	arg_tmp;
	int	i;

	i = 2;
	while (av[i])
	{
		if (ft_verif_max_int(av[i]) == -1)
			return (-1);
		arg_tmp = ft_atoi(av[i]);
		if (arg_tmp < 1)
		{
			ft_putendl_fd("Error : wrong number", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_verif_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_putendl_fd("Error : bad arguments required", 2);
		return (-1);
	}
	if (ft_verif_digit(av) == -1)
		return (-1);
	if (ft_verif_nber_philo(av) == -1)
		return (-1);
	if (ft_verif_time_to(av) == -1)
		return (-1);
	return (0);
}
