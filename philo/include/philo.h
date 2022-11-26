/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:40 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/26 18:23:42 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define END -2

typedef struct s_philo
{
	int					pos_philo;
	pthread_t			thread;
	int					fork_right;
	int					fork_left;
	struct s_banquet	*banquet;
}	t_philo;

typedef struct s_banquet
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	long long 		time_start;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_fork;
	t_philo			*philo;
}	t_banquet;

/*verif_arg*/
int		ft_verif_arg(int ac, char **av);
int		ft_verif_digit(char **av);
int		ft_verif_nber_philo(char **av);
int		ft_verif_time_to(char **av);

/*init*/
int		ft_init(t_banquet *banquet, int ac, char **av);
int		ft_init_banquet(t_banquet *banquet, int ac, char **av);
int		ft_init_philo(t_banquet *banquet);

/*philosophers*/
int		ft_philo(t_banquet *banquet);

/*utils*/
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	ft_putendl_fd(char *s, int fd);

/*free*/
void	ft_free(t_banquet *banquet);

#endif
