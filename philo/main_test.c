#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void	*start_routine()
{
	pthread_mutex_lock(&mutex);
	printf("mange\n");
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);

}

void	*start_routine2()
{
	pthread_mutex_lock(&mutex);
	printf("dodo\n");
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);

}

int	main()
{
	int	i;
	int size;

	size = 10;
	pthread_t th[size];
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < size)
	{
		pthread_create(&th[i], NULL, &start_routine, NULL);
		pthread_create(&th[i], NULL, &start_routine2, NULL);

		i++;
	}
	while (i < size)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
