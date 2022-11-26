/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:57:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/26 18:26:45 by clorcery         ###   ########.fr       */
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

long long	ft_time_start()
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

long long	ft_change_time(t_banquet *banquet)
{
	long  long 	time;
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

int	ft_display(t_philo *philo, t_banquet *banquet, char *s)
{
	int	time_milli;
	time_milli = ft_change_time(banquet);
	if (time_milli == -1)
		return (-1);
	pthread_mutex_lock(&banquet->mutex_print);	
	printf("%d %d %s\n",time_milli, philo->pos_philo, s);
	pthread_mutex_unlock(&banquet->mutex_print);	
	return (0);
}

int	ft_verif_time_die(t_banquet *banquet)
{

	return (0);
}

void	*start_routine(void *struc)
{
	t_philo			*philo;
	t_banquet 		*banquet;

	philo = (t_philo *)struc;
	banquet = (t_banquet *)philo->banquet;
	if (philo->pos_philo % 2 == 0)
		usleep(50);
	else
		usleep(80);
	while (ft_verif_time_die(banquet) != END)
	{
	///
		pthread_mutex_lock(&banquet->mutex_fork[philo->fork_left]);
		if (ft_display(philo, banquet, "has taken a fork") == -1)
			return (NULL);
	///	
		pthread_mutex_lock(&banquet->mutex_fork[philo->fork_right]);
		if (ft_display(philo, banquet, "has taken a fork") == -1)
			return (NULL);
	///	
		if (ft_display(philo, banquet, "is eating") == -1)
			return (NULL);
		usleep(banquet->time_eat);
		pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_right]);
		pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_left]);

		if (ft_display(philo, banquet, "is sleeping") == -1)
			return (NULL);
		usleep(banquet->time_sleep);

		if (ft_display(philo, banquet, "is thinking") == -1)
			return (NULL);

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
	return (0);
}

int	ft_destroy_mutex(t_banquet *banquet)
{
	int	i;

	i = banquet->nb_philo - 1;
	while (i >= 0)
	{	
		if (pthread_join(banquet->philo[i].thread, NULL) != 0)
		{
			ft_putendl_fd("Error : pthread_join", 2);
			return (-1);
		}
		if (pthread_mutex_destroy(&banquet->mutex_fork[i]) != 0)
		{
			ft_putendl_fd("Error : mutex destroy", 2);
			return (-1);
		}
		i--;
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
