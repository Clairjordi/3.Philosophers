/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:57:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/05 16:00:03 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_thread_join(t_banquet *banquet)
{
	int	i;

	i = banquet->nb_philo - 1;
	if (pthread_join(banquet->th_death, NULL) != 0)
	{
		ft_putendl_fd("Error : pthread_join", 2);
		return (-1);
	}
	while (i >= 0)
	{	
		if (pthread_join(banquet->philo[i].thread, NULL) != 0)
		{
			ft_putendl_fd("Error : pthread_join", 2);
			return (-1);
		}
		i--;
	}
	return (0);
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
	if (ft_thread_join(banquet) == -1)
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
