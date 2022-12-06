/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:54:32 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/06 14:18:06 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_get_time_eat(t_philo *philo)
{
	long	ret;
	int		res;

	res = pthread_mutex_lock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = philo->time_last_eat;
	res = pthread_mutex_unlock(&philo->mutex_val);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (ret);
}

int	ft_get_nb_eat(t_banquet *banquet, int i)
{
	int	ret;
	int	res;

	res = pthread_mutex_lock(&banquet->philo[i].mutex_val);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	ret = banquet->philo[i].nb_eat;
	res = pthread_mutex_unlock(&banquet->philo[i].mutex_val);
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
	while (i < banquet->nb_philo)
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
