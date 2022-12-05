/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:18:22 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/05 16:18:25 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_create_mutex_fork(t_banquet *banquet)
{
	int	i;
	int	ret;

	i = 0;
	while (i < banquet->nb_philo)
	{
		ret = pthread_mutex_init(&banquet->mutex_fork[i], NULL);
		if (ret != 0)
		{
			ft_putendl_fd("Error : init mutex failed", 2);
			ft_free(banquet);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_destroy_mutex(t_banquet *banquet)
{
	int	i;
	int	res;

	i = banquet->nb_philo - 1;
	while (i >= 0)
	{	
		res = pthread_mutex_destroy(&banquet->mutex_fork[i]);
		if (ft_verif_res(res, "Mutex destroy, fork") == -1)
			return (-1);
		res = pthread_mutex_destroy(&banquet->philo[i].mutex_val);
		if (ft_verif_res(res, "Mutex destroy, val") == -1)
			return (-1);
		i--;
	}
	if (pthread_mutex_destroy(&banquet->mutex_print) != 0)
	{
		ft_putendl_fd("Error : mutex destroy, print", 2);
		return (-1);
	}
	if (pthread_mutex_destroy(&banquet->mutex_die) != 0)
	{
		ft_putendl_fd("Error : mutex destroy, die", 2);
		return (-1);
	}
	return (0);
}
