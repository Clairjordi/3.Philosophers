/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:22:21 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/03 17:00:40 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_display(t_philo *philo, t_banquet *banquet, char *s)
{
	int	time_milli;
	int	res;

	time_milli = ft_change_time(banquet);
	if (time_milli == -1)
		return (-1);
	res = pthread_mutex_lock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex lock") == -1)
		return (-1);
	if (ft_get_end(banquet) == FALSE)
		printf("%d %d %s\n", time_milli, philo->pos_philo, s);
	res = pthread_mutex_unlock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
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
	printf("%d %d %s\n", time_milli, philo->pos_philo, s);
	res = pthread_mutex_unlock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}
