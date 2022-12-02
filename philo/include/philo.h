/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:40 by clorcery          #+#    #+#             */
/*   Updated: 2022/12/02 18:55:58 by clorcery         ###   ########.fr       */
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
# define TRUE 0
# define FALSE 1

typedef struct s_philo
{
	int					pos_philo;
	pthread_t			thread;
	long				time_eat;
	int					nb_eat;
	int					fork_right;
	int					fork_left;
	pthread_mutex_t		mutex_val;
	struct s_banquet	*banquet;
}	t_philo;

typedef struct s_banquet
{
	int				nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_must_eat;
	long 			time_start;
	int				end;
	pthread_t		th_death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	*mutex_fork;
	t_philo			*philo;
}	t_banquet;

/*verif_arg*/
int			ft_verif_arg(int ac, char **av);
int			ft_verif_digit(char **av);
int			ft_verif_nber_philo(char **av);
int			ft_verif_time_to(char **av);

/*init*/
int			ft_init(t_banquet *banquet, int ac, char **av);
int			ft_init_banquet(t_banquet *banquet, int ac, char **av);
int			ft_init_philo(t_banquet *banquet);

/*philosophers*/
int			ft_is_thinking(t_philo *philo);
void		*start_routine(void *struc);
int			ft_create_thread(t_banquet *banquet);
int			ft_philo(t_banquet *banquet);

/*mutex*/
int			ft_create_mutex_fork(t_banquet *banquet);
int			ft_destroy_mutex(t_banquet *banquet);

/*display*/
int			ft_display(t_philo *philo, t_banquet *banquet, char *s);
int			ft_display_die(t_philo *philo, t_banquet *banquet, char *s);

/*eat*/
int			ft_set_time_eat(t_philo *philo);
int			ft_recup_info_eat(t_philo *philo, t_banquet *banquet);
int			ft_is_eating(t_philo *philo, t_banquet *banquet);

/*die*/
void		*ft_verif_die(void	*struc);

/*die_util*/
int			ft_get_time_eat(t_philo *philo);
int			ft_get_nb_eat(t_banquet *banquet, int i);
int			ft_philo_nb_eat(t_banquet *banquet);
int			ft_get_end(t_banquet *banquet);

/*time*/
long		ft_time_start(void);
long		ft_change_time(t_banquet *banquet);
int			ft_usleep(t_banquet *banquet, long time_to_wait);

/*utils*/
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
void		ft_putendl_fd(char *s, int fd);
int			ft_verif_res(int result, char *s);

/*free*/
void		ft_free(t_banquet *banquet);

#endif
