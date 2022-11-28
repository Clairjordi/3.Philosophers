/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:57:47 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/28 14:18:56 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

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

int	ft_get_value(t_philo *philo)
{
	int	ret;
	int	res;

	res = pthread_mutex_lock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = philo->time_eat;
	res = pthread_mutex_unlock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (ret);
}

int	ft_set_value(t_philo *philo)
{
	int	res;

	res = pthread_mutex_lock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	philo->time_eat = ft_change_time(philo->banquet);
	if (philo->time_eat == -1)
		return (-1);
	res = pthread_mutex_unlock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}

int	ft_recup_info_eat(t_philo *philo, t_banquet *banquet)
{
	ft_set_value(philo);
	if (banquet->nb_must_eat != -1)
		philo->nb_eat += 1;
	return (0);
}

int	ft_usleep(t_banquet *banquet, int time_to_wait)
{
	int	current_time;
	int	res;

	current_time = ft_change_time(banquet);
	if (current_time == -1)
		return (-1);
	while (current_time + (time_to_wait / 1000) > ft_change_time(banquet))
	{
		if (ft_get_end(banquet) == TRUE)
			break ;
		res = usleep(25);
		if (ft_verif_res(res, "usleep") == -1)
			return (-1);
	}
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
	if (ft_usleep(banquet, banquet->time_eat) == -1) //ft_usleep
		return (-1);
	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_right]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	res = pthread_mutex_unlock(&banquet->mutex_fork[philo->fork_left]);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}

int	ft_get_eat(t_banquet *banquet, int i)
{
	int	ret;
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_die);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = banquet->philo[i].nb_eat;
	//dprintf(2, "nb_eat = %d\n", banquet->philo[i].nb_eat);
	res = pthread_mutex_unlock(&banquet->mutex_die);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (ret);
}

int	ft_philo_nb_eat(t_banquet *banquet)
{
	int	i;
	int	eat_ok;

	i = 0;
	eat_ok = 0;
	while(i < banquet->nb_philo)
	{
		if (ft_get_eat(banquet, i) == banquet->nb_must_eat)
			eat_ok++;	
		i++;
	}
	if (eat_ok == i)
		return (TRUE);
	return (FALSE);
}

int	ft_display_die(t_philo *philo, t_banquet *banquet, char *s)
{
	int	time_milli;
	int	res;

	time_milli = ft_change_time(banquet);
	if (time_milli == -1)
		return (-1);
	res = pthread_mutex_lock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	printf("%d %d %s\n",time_milli, philo->pos_philo, s);
	res = pthread_mutex_unlock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}
void	*ft_verif_die(void	*struc)
{
	t_banquet 		*banquet;
	int	result;
	int	tmp;
	int	i;

	banquet = (t_banquet *)struc;
	i = 0;
	while (1)
	{
		usleep(50);
		result = ft_change_time(banquet);

		result = result - ft_get_value(&banquet->philo[i]);
		tmp = banquet->time_die / 1000;
		if (result > tmp)
		{
			pthread_mutex_lock(&banquet->mutex_die);
			if (ft_display_die(&banquet->philo[i], banquet, "\033[1;31mdied\033[0;0m") == -1)
				return (NULL);
			banquet->end = TRUE; 
			pthread_mutex_unlock(&banquet->mutex_die);
			break ;	
		}
		if (banquet->nb_must_eat != -1 && ft_philo_nb_eat(banquet) == TRUE)
		{
			pthread_mutex_lock(&banquet->mutex_die);
			banquet->end = TRUE; 
			pthread_mutex_unlock(&banquet->mutex_die);
			break ;
		}
		i++;
		if (i == banquet->nb_philo - 1)
			i = 0;
	}
	return (NULL);
}


void	*start_routine(void *struc)
{
	t_philo			*philo;
	t_banquet 		*banquet;

	philo = (t_philo *)struc;
	banquet = (t_banquet *)philo->banquet;
	while (ft_get_end(banquet) == FALSE)
	{
		if (ft_is_thinking(philo) == -1)
			return (NULL);
		if (ft_get_end(banquet) == FALSE)
		{
			if (ft_is_eating(philo, banquet) == -1)
				return (NULL);
		}
		if (ft_get_end(banquet) == FALSE)
		{
			if (ft_display(philo, banquet, "\033[1;33mis sleeping\033[0;0m") == -1)
				return (NULL);
			ft_usleep(banquet, banquet->time_sleep);
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
