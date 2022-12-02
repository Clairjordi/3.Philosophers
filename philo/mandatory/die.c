/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:36:19 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/02 18:37:55 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_get_time_eat(t_philo *philo)
{
	long	ret;
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

int	ft_get_nb_eat(t_banquet *banquet, int i)
{
	int	ret;
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_die);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = banquet->philo[i].nb_eat;
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
		if (ft_get_nb_eat(banquet, i) == banquet->nb_must_eat)
			eat_ok++;	
		i++;
	}
	if (eat_ok == i)
		return (TRUE);
	return (FALSE);
}

int	ft_get_end(t_banquet *banquet)
{
	int	ret;
	int	res;

	res = pthread_mutex_lock(&banquet->mutex_die);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = banquet->end;
	res = pthread_mutex_unlock(&banquet->mutex_die);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (ret);
}

void	*ft_verif_die(void	*struc)
{
	t_banquet 		*banquet;
	long	result;
	long	tmp;
	int	i;

	banquet = (t_banquet *)struc;
	i = 0;
	while (1)
	{
		usleep(50);
		result = ft_change_time(banquet);
		result = result - ft_get_time_eat(&banquet->philo[i]);
		tmp = banquet->time_die;
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

