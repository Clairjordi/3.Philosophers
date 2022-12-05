/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:21:05 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/05 15:38:23 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_time_start(void)
{
	long long		time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putendl_fd("Error : gettimofday time_start", 2);
		return (-1);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	ft_change_time(t_banquet *banquet)
{
	long			time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putendl_fd("Error : gettimeofday", 2);
		return (-1);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = time - banquet->time_start;
	return (time);
}

static int	ft_usleep_bis(t_banquet *banquet, int time)
{
	int	res;

	while (time / 100 > ft_change_time(banquet) / 100)
	{
		if (ft_get_end(banquet) == TRUE)
			break ;
		res = usleep(1000);
		if (ft_verif_res(res, "usleep") == -1)
			return (-1);
	}
	return (0);
}

int	ft_usleep(t_banquet *banquet, long time_to_wait)
{
	long	time;
	int		res;

	time = ft_change_time(banquet);
	if (time == -1)
		return (-1);
	time += time_to_wait;
	if (time_to_wait >= 50)
	{
		if (ft_usleep_bis(banquet, time) == -1)
			return (-1);
	}
	while (time > ft_change_time(banquet))
	{
		if (ft_get_end(banquet) == TRUE)
			break ;
		res = usleep(500);
		if (ft_verif_res(res, "usleep") == -1)
			return (-1);
	}
	return (0);
}
