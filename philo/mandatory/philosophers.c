/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:57:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/02 20:30:23 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_thinking(t_philo *philo)
{
	t_banquet	*banquet;

	banquet = (t_banquet *)philo->banquet;
	if (ft_display(philo, banquet, "\033[1;35mis thinking\033[0;0m") == -1)
		return (-1);
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

int	ft_is_eating_one(t_philo *philo, t_banquet *banquet)
{
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_display(philo, banquet, "\033[1;32mhas taken a fork\033[0;0m") == -1)
		return (-1);
	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	res = usleep(banquet->time_die);
	if (res == -1)
		return (-1);
	banquet->end = TRUE;
	return (0);
}

void	*start_routine(void *struc)
{
	t_philo		*philo;
	t_banquet	*banquet;

	philo = (t_philo *)struc;
	banquet = (t_banquet *)philo->banquet;
	if (philo->pos_philo % 2 == 0)
		usleep(1000);
	while (ft_get_end(banquet) == FALSE)
	{
		if (ft_is_thinking(philo) == -1)
			return (NULL);
		if (ft_get_end(banquet) == FALSE)
		{
			if (banquet->nb_philo == 1)
			{	
				if (ft_is_eating_one(philo, banquet) == -1)
					return (NULL);
			}
			else if (ft_is_eating(philo, banquet) == -1)
				return (NULL);
		}
		if (ft_get_end(banquet) == FALSE)
		{
			if (ft_is_sleeping(philo, banquet) == -1)
				return (NULL);
		}
	}
	return (NULL);
}

int	ft_create_thread(t_banquet *banquet)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = banquet->philo;
	banquet->time_start = ft_time_start();
	while (i < banquet->nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, start_routine,
				&(philo[i])) != 0)
		{
			ft_putendl_fd("Error : pthread_create", 2);
			return (-1);
		}	
		i++;
	}	
	if (pthread_create(&banquet->th_death, NULL, ft_verif_die,
			banquet) != 0)
	{
		ft_putendl_fd("Error : pthread_create", 2);
		return (-1);
	}
	return (0);
}

int	ft_philo(t_banquet *banquet)
{
	if (ft_create_mutex_fork(banquet) == 1)
	{
		ft_free(banquet);
		return (-1);
	}
	if (ft_create_thread(banquet) == 1)
	{
		ft_free(banquet);
		return (-1);
	}
	if (ft_destroy_mutex(banquet) == 1)
	{
		ft_free(banquet);
		return (-1);
	}
	return (0);
}
