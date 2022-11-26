/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:25:24 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/26 10:41:31 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_banquet *banquet)
{
	/* int	i; */
    /*  */
	/* i = 0; */
	if (banquet->mutex_fork != NULL)
	{
		/* while (i < banquet->nb_philo) */
		/* { */
		/* 	if (banquet->mutex_fork[i] != NULL) */
		/* 		free(banquet->mutex_fork[i]); */
		/* 	i++; */
		/* } */
		free(banquet->mutex_fork);
	}
	free(banquet->philo);
}
