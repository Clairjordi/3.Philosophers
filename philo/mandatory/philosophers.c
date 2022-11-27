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

//pthread_mutex_lock(&banquet->mutex_print);
//printf("\n");
//pthread_mutex_unlock(&banquet->mutex_print);

int	ft_is_thinking(t_philo *philo)
{
	t_banquet 		*banquet;

	banquet = (t_banquet *)philo->banquet;
	if (philo->pos_philo % 2 == 0)
		usleep(50);
	else
		usleep(80);
	if (ft_display(philo, banquet, "\033[1;35mis thinking\033[0;0m") == -1)
		return (-1);
	return (0);
}

int	ft_recup_info_eat(t_philo *philo, t_banquet *banquet)
{
	philo->time_eat = ft_change_time(banquet);
	if (philo->time_eat == -1)
		return (-1);
	philo->had_eat = TRUE;
	if (banquet->nb_must_eat != -1)
		philo->nb_eat += 1;
	return (0);
}

int	ft_is_eating(t_philo *philo, t_banquet *banquet)
{
	int	res;
	
	res = pthread_mutex_lock(&banquet->mutex_fork[philo->fork_left]);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_display(philo, banquet, "\033[1;32mhas taken a fork\033[0;0m") == -1)
		return (-1);
	res = pthread_mutex_lock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_display(philo, banquet, "\033[1;32mhas taken a fork\033[0;0m") == -1)
		return (-1);
	if (ft_recup_info_eat(philo, banquet) == -1) // bien place ??
		return (-1);
	if (ft_display(philo, banquet, "\033[1;34mis eating\033[0;0m") == -1)
		return (-1);
	res = usleep(banquet->time_eat);
	if (ft_verif_res(res, "usleep") == -1)
		return (-1);
	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_left]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}

int	ft_philo_nb_eat(t_banquet *banquet)
{
	int	i;
	int	eat_ok;

	i = 0;
	eat_ok = 0;
	while(i < banquet->nb_philo)
	{
		if (banquet->philo[i].nb_eat == banquet->nb_must_eat)
			eat_ok++;	
		i++;
	}
	if (eat_ok == i)
		return (TRUE);
	return (FALSE);
}

int	ft_verif_die(t_philo *philo, t_banquet *banquet)
{
	int	current_time;
	int	result;
	int	tmp;

	current_time = ft_change_time(banquet);
	if (philo->had_eat == FALSE && current_time > banquet->time_die)
	{
		banquet->end = TRUE;
		philo->dead_philo = TRUE;
		return (END);
	}
	if (philo->had_eat == TRUE)
	{
		result = current_time - philo->time_eat;
		tmp = banquet->time_die / 1000;
		pthread_mutex_lock(&banquet->mutex_print);
		printf("result = %d - tmp = %d\n", result, tmp);
		pthread_mutex_unlock(&banquet->mutex_print);
		if (result > tmp)
		{
			banquet->end = TRUE;
			philo->dead_philo = TRUE;
			return (END);
		}
	}
	if (banquet->nb_must_eat != -1 && philo->nb_eat == banquet->nb_must_eat)
	{
		if (ft_philo_nb_eat(banquet) == TRUE)
		{
			banquet->end = TRUE;
			return (END);
		}
	}
	return (0);
}

void	*start_routine(void *struc)
{
	t_philo			*philo;
	t_banquet 		*banquet;

	philo = (t_philo *)struc;
	banquet = (t_banquet *)philo->banquet;
	while (ft_verif_die(philo, banquet) != END)
	{
		if (ft_is_thinking(philo) == -1)
			return (NULL);
		if (ft_verif_die(philo, banquet) != END)
		{
			if (ft_is_eating(philo, banquet) == -1)
				return (NULL);
		}
		if (ft_verif_die(philo, banquet) != END)
		{
			if (ft_display(philo, banquet, "\033[1;33mis sleeping\033[0;0m") == -1)
				return (NULL);
			usleep(banquet->time_sleep);
		}
		if (banquet->end == TRUE) 
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
	while (i < banquet->nb_philo && banquet->end == FALSE)
	{
		if (pthread_create(&(philo[i].thread), NULL, start_routine,
			&(philo[i])) != 0)
		{
			ft_putendl_fd("Error : pthread_create", 2);
			return (-1);
		}
		i++;
	}
	if (banquet->end == TRUE)
		printf("it's over\n");
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
