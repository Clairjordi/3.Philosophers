/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:33:39 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/28 12:36:31 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_banquet	banquet;

	if (ft_verif_arg(argc, argv) == -1)
		return (1);
	if (ft_init(&banquet, argc, argv) == -1)
		return (1);
	if (ft_philo(&banquet) == -1)
		return (1);
	ft_free(&banquet);
	return (0);
}
