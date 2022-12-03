/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:37:12 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/03 16:31:13 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_banquet(t_banquet *banquet, int ac, char **av)
{
	int	res;

	banquet->nb_philo = ft_atoi(av[1]);
	banquet->time_die = ft_atoi(av[2]);
	banquet->time_eat = ft_atoi(av[3]);
	banquet->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		banquet->nb_must_eat = ft_atoi(av[5]);
	else
		banquet->nb_must_eat = -1;
	banquet->end = FALSE;
	res = pthread_mutex_init(&banquet->mutex_print, NULL);
	if (ft_verif_res(res, "Mutex init"))
		return (-1);
	res = pthread_mutex_init(&banquet->mutex_die, NULL);
	if (ft_verif_res(res, "Mutex init"))
		return (-1);
	banquet->mutex_fork = malloc(sizeof(pthread_mutex_t) * banquet->nb_philo);
	if (!banquet->mutex_fork)
	{
		ft_putendl_fd("Error : Malloc", 2);
		return (-1);
	}
	return (0);
}

static void	ft_init_philo_bis(t_philo *philo, int i)
{
	philo[i].pos_philo = i + 1;
	philo[i].fork_right = i;
	if (i > 0)
		philo[i].fork_left = i - 1;
	philo[i].time_eat = 0;
	philo[i].nb_eat = 0;
}

int	ft_init_philo(t_banquet *banquet)
{
	int		i;
	t_philo	*philo;
	int		res;

	i = 0;
	banquet->philo = malloc(sizeof(t_philo) * banquet->nb_philo);
	if (!banquet->philo)
	{
		ft_putendl_fd("Error : Malloc", 2);
		ft_free(banquet);
		return (-1);
	}
	philo = banquet->philo;
	while (i < banquet->nb_philo)
	{
		ft_init_philo_bis(philo, i);
		philo[i].banquet = banquet;
		res = pthread_mutex_init(&philo[i].mutex_val, NULL);
		if (ft_verif_res(res, "Mutex init"))
			return (-1);
		i++;
	}
	if (banquet->nb_philo != 1)
		philo[0].fork_left = i - 1;
	return (0);
}

int	ft_init(t_banquet *banquet, int ac, char **av)
{
	if (ft_init_banquet(banquet, ac, av) == -1)
		return (-1);
	if (ft_init_philo(banquet) == -1)
		return (-1);
	return (0);
}
