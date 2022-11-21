

#include "../../include/philo.h"

int	ft_verif_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
			{
				ft_putendl_fd("Error : digit requiered", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_verif_nber_philo(char **av)
{
	int	tmp;

	tmp = ft_atoi(av[1]);
	
	if (tmp < 1)
	{
		ft_putendl_fd("Error : not enough philosophers", 2);
		return (1);
	}
	return (0);
}

int	ft_verif_time_to(char **av)
{
	int	arg_tmp;
	int	i;

	i = 1;
	while (av[i])
	{
		arg_tmp = ft_atoi(av[i]);
		if (arg_tmp < 0)
		{
			ft_putendl_fd("Error : positive number required", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_verif_arg(int ac, char **av)
{
	if (ac != 5)
	{
		ft_putendl_fd("Error : bad arguments requeried", 2);
		return (1);
	}
	if (ft_verif_digit(av) == 1)
		return (1);
	if (ft_verif_nber_philo(av) == 1)
		return (1);
	if (ft_verif_time_to(av) == 1)
		return (1);
	return (0);
}
