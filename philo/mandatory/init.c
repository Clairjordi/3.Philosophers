/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:37:12 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/26 14:51:55 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_recup_time_to(char *av)
{
	int	time_to;

	time_to = ft_atoi(av);
	time_to *= 1000;
	return (time_to);
}

int	ft_init_banquet(t_banquet *banquet, int ac, char **av)
{
	banquet->nb_philo = ft_atoi(av[1]);
	banquet->time_die = ft_recup_time_to(av[2]);
	banquet->time_eat = ft_recup_time_to(av[3]);
	banquet->time_sleep = ft_recup_time_to(av[4]);
	if (ac == 6)
		banquet->nb_must_eat = ft_atoi(av[5]);
	else
		banquet->nb_must_eat = -1;
	if (pthread_mutex_init(&banquet->mutex_print, NULL) != 0)
	{
		ft_putendl_fd("Error : Mutex init", 2);
		return (-1);
	}
	banquet->mutex_fork = malloc(sizeof(pthread_mutex_t) * banquet->nb_philo);
	if (!banquet->mutex_fork)
	{
		ft_putendl_fd("Error : Malloc", 2);
		return (-1);
	}
	return (0);
}

int	ft_init_philo(t_banquet *banquet)
{
	int		i;
	t_philo	*philo;

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
		philo[i].pos_philo = i + 1;
		philo[i].fork_right = i;
		if (i > 0)
			philo[i].fork_left = i - 1;
		philo[i].banquet = banquet;
		i++;
	}
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
