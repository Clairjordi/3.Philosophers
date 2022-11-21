/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:40 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/18 14:15:10 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

//ARG
/*verif_arg*/
int ft_verif_arg(int ac, char **av);
int ft_verif_digit(char **av);
int ft_verif_nber_philo(char **av);
int ft_verif_time_to(char **av);

//UTILS
/*utils*/
int ft_isdigit(int c);
int ft_atoi(const char *nptr);
void    ft_putendl_fd(char *s, int fd);

#endif
