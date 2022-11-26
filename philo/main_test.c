#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct s_my_struct
{
	int 			nb_du_philo; // int i; nb_du+philo = i;
	int 			size;
	pthread_mutex_t m_fork;
	pthread_mutex_t mutex;
	pthread_t th[10];
} t_p;

void	*start_routine(void *lol)
{
	t_p *p; 

	p = (t_p *)lol;

	pthread_mutex_lock(&p->mutex);
	pthread_mutex_lock(&p->m_fork);
	printf("philo %d mange\n", p->nb_du_philo);
	pthread_mutex_unlock(&p->m_fork);
	usleep(60000);
	pthread_mutex_unlock(&p->mutex);
	pthread_mutex_lock(&p->mutex);
	pthread_mutex_lock(&p->m_fork);
	//write(1, "dort\n", 5);
	printf("philo %d dort\n", p->nb_du_philo);
	pthread_mutex_unlock(&p->m_fork);
	usleep(60000);
	pthread_mutex_unlock(&p->mutex);
	return (NULL);

}

int	main()
{
	t_p p;
	int	i;
	int	j;

	//p = malloc(sizeof(t_p));
	p.size = 10;
	//pthread_t th[p.size];
	pthread_mutex_init(&p.mutex, NULL);
	pthread_mutex_init(&p.m_fork, NULL);
	j = 0;
	while (j < p.size)
	{ 
		pthread_create(&p.th[j], NULL, start_routine, &p);
		p.nb_du_philo = j + 1;
		if (j % 2 == 0)
			usleep(50);
		else
			usleep(100);
		j++;
	}
	i = 0;
	while (i < p.size)
	{
		pthread_join(p.th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&p.mutex);
	pthread_mutex_destroy(&p.m_fork);
	//free(p);
	return (0);
}
