
#include "../include/philo.h"

long long	ft_time_start()
{
	long long		time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putendl_fd("Error : gettimofday time_start", 2);
		return (-1);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long long	ft_change_time(t_banquet *banquet)
{
	long  long 		time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putendl_fd("Error : gettimeofday", 2);
		return (-1);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = time - banquet->time_start;
	return (time);
}

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
	printf("%d %d %s\n",time_milli, philo->pos_philo, s);
	res = pthread_mutex_unlock(&banquet->mutex_print);
	if (ft_verif_res(res, "Mutex unlock") == -1)
		return (-1);
	return (0);
}
