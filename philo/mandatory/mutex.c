
#include "../include/philo.h"

int	ft_create_mutex_fork(t_banquet *banquet)
{
	int	i;
	int	ret;

	i = 0;
	while (i < banquet->nb_philo)
	{
		ret = pthread_mutex_init(&banquet->mutex_fork[i], NULL);
		if (ret != 0)
		{
			ft_putendl_fd("Error : init mutex failed", 2);
			ft_free(banquet);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_destroy_mutex(t_banquet *banquet)
{
	int	i;

	//i = 0;
	i = banquet->nb_philo - 1;
	while /*(i < banquet->nb_philo)*/(i >= 0)
	{	
		if (pthread_join(banquet->philo[i].thread, NULL) != 0)
		{
			ft_putendl_fd("Error : pthread_join", 2);
			return (-1);
		}
		if (pthread_mutex_destroy(&banquet->mutex_fork[i]) != 0)
		{
			ft_putendl_fd("Error : mutex destroy, fork", 2);
			return (-1);
		}
		//i++;
		i--;
	}
	if (pthread_mutex_destroy(&banquet->mutex_print) != 0)
	{
		ft_putendl_fd("Error : mutex destroy, print", 2);
		return (-1);
	}

	return (0);
}
