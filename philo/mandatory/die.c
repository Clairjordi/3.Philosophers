/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:36:19 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/04 20:30:14 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_verif_die_bis(t_banquet *banquet, int i, int res)
{
	long		result;
	long		tmp;

	result = ft_change_time(banquet);
	if (result == -1)
		return (-1);
	tmp = ft_get_time_eat(&banquet->philo[i]);
	if (tmp == -1)
		return (-1);
	result -= tmp;
	if (result > banquet->time_die)
	{	
		res = pthread_mutex_lock(&banquet->mutex_die);
		if (ft_verif_res(res, "Mutex lock") == -1)
			return (-1);
		if (ft_display_die(&banquet->philo[i], banquet,
				"\033[1;31mdied\033[0;0m") == -1)
			return (-1);
		banquet->end = TRUE;
		res = pthread_mutex_unlock(&banquet->mutex_die);
		if (ft_verif_res(res, "Mutex unlock") == -1)
			return (-1);
		return (2);
	}
	return (0);
}

static int	ft_verif_die_ter(t_banquet *banquet, int res)
{
	if (banquet->nb_must_eat != -1 && ft_philo_nb_eat(banquet) == TRUE)
	{
		res = pthread_mutex_lock(&banquet->mutex_die);
		if (ft_verif_res(res, "Mutex lock") == -1)
			return (-1);
		banquet->end = TRUE;
		res = pthread_mutex_unlock(&banquet->mutex_die);
		if (ft_verif_res(res, "Mutex unlock") == -1)
			return (-1);
		return (2);
	}
	return (0);
}

void	*ft_verif_die(void	*struc)
{
	t_banquet	*banquet;
	int			i;
	int			res;

	banquet = (t_banquet *)struc;
	i = 0;
	res = 0;
	while (1)
	{
		res = ft_verif_die_bis(banquet, i, res);
		if (res == 2)
			break ;
		if (res == -1)
			return (NULL);
		res = ft_verif_die_ter(banquet, res);
		if (res == 2)
			break ;
		if (res == -1)
			return (NULL);
		i++;
		if (banquet->nb_philo == 1 || i == banquet->nb_philo - 1)
		{
			i = 0;
			usleep(500);
		}
	}
	return (NULL);
}
