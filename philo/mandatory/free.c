/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:25:24 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/02 19:37:51 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_banquet *banquet)
{
	if (banquet->mutex_fork != NULL)
	{
		free(banquet->mutex_fork);
	}
	free(banquet->philo);
}
