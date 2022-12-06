/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:30:11 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/06 14:16:08 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_set_time_eat(t_philo *philo)
{
	int	res;

	res = pthread_mutex_lock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	philo->time_last_eat = ft_change_time(philo->banquet);
	if (philo->time_last_eat == -1)
		return (-1);
	res = pthread_mutex_unlock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}

int	ft_recup_info_eat(t_philo *philo, t_banquet *banquet)
{
	int	res;

	res = ft_set_time_eat(philo);
	if (res == -1)
		return (-1);
	if (banquet->nb_must_eat > 0)
	{	
		res = pthread_mutex_lock(&philo->mutex_val);
		if (ft_verif_res(res, "Mutex lock") == -1)
			return (-1);
		philo->nb_eat += 1;
		res = pthread_mutex_unlock(&philo->mutex_val);
		if (ft_verif_res(res, "Mutex unlock") == -1)
			return (-1);
	}
	return (0);
}

static int	ft_is_eating_bis(t_philo *philo, t_banquet *banquet)
{
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_fork[philo->fork_left]);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_display(philo, banquet,
			"\033[1;32mhas taken a fork\033[0;0m") == -1)
		return (-1);
	if (ft_recup_info_eat(philo, banquet) == -1)
		return (-1);
	if (ft_display(philo, banquet,
			"\033[1;34mis eating\033[0;0m") == -1)
		return (-1);
	if (ft_usleep(banquet, banquet->time_eat) == -1)
		return (-1);
	return (0);
}

static int	ft_is_eating_ter(t_philo *philo, t_banquet *banquet)
{
	int	res;

	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	if (banquet->nb_philo > 1)
	{
		res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_left]);
		if (ft_verif_res(res, "Mutex unlock") == -1)
			return (-1);
	}
	return (0);
}

int	ft_is_eating(t_philo *philo, t_banquet *banquet)
{
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_display(philo, banquet, "\033[1;32mhas taken a fork\033[0;0m") == -1)
		return (-1);
	if (banquet->nb_philo > 1)
	{
		if (ft_is_eating_bis(philo, banquet) == -1)
			return (-1);
	}
	else
	{
		if (ft_usleep(banquet, banquet->time_die * 1.1) == -1)
			return (-1);
	}
	if (ft_is_eating_ter(philo, banquet) == -1)
		return (-1);
	return (0);
}
