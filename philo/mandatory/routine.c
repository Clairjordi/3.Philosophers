/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:14:38 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/05 19:00:43 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_thinking(t_philo *philo)
{
	t_banquet	*banquet;
	long		time;
	long		time_think;

	banquet = (t_banquet *)philo->banquet;
	time = ft_change_time(banquet) - philo->time_last_eat;
	time_think = (banquet->time_die - time) - 10;
	if (time_think <= 0)
		return (0);
	if (ft_display(philo, banquet, "\033[1;35mis thinking\033[0;0m") == -1)
		return (-1);
	ft_usleep(banquet, time_think);
	return (0);
}

int	ft_is_sleeping(t_philo *philo, t_banquet *banquet)
{
	int	res;

	if (ft_display(philo, banquet,
			"\033[1;33mis sleeping\033[0;0m") == -1)
		return (-1);
	res = ft_usleep(banquet, banquet->time_sleep);
	if (res == -1)
		return (-1);
	return (0);
}

static int	ft_start_routine_bis(t_philo *philo, t_banquet *banquet)
{
	if (philo->pos_philo % 2 == 0)
	{
		if (ft_display(philo, banquet, "\033[1;35mis thinking\033[0;0m") == -1)
			return (-1);
		if (ft_usleep(banquet, banquet->time_eat) == -1)
			return (-1);
	}
	return (0);
}

void	*start_routine(void *struc)
{
	t_philo		*philo;
	t_banquet	*banquet;

	philo = (t_philo *)struc;
	banquet = (t_banquet *)philo->banquet;
	if (ft_start_routine_bis(philo, banquet) == -1)
		return (NULL);
	while (ft_get_end(banquet) == FALSE)
	{
		if (ft_get_end(banquet) == FALSE)
		{
			if (ft_is_eating(philo, banquet) == -1)
				return (NULL);
		}
		if (ft_get_end(banquet) == FALSE)
		{
			if (ft_is_sleeping(philo, banquet) == -1)
				return (NULL);
		}	
		if (ft_is_thinking(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
