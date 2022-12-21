# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_moh
{
	pthread_t p1, p2;
	pthread_mutex_t lock1, lock2;
	int *tab;
}	t_moh;

void *routine(void *arg)
{
	int dieri;
	pthread_mutex_t ok;
	dieri = *(int *)arg;

	// pthread_mutex_init(&ok, NULL);
	// pthread_mutex_lock(&ok);
	if (dieri == 42)
		usleep(500);
	printf("i=%i\n", dieri);
	// pthread_mutex_unlock(&ok);
}

int	main(int ac, char **av)
{
	t_moh dieri;
	int	i[2];
	pthread_t p1, p2;
	pthread_mutex_t lock1, lock2;

	i[0] = 42;
	i[1] = 92110;
	dieri.tab = i;
	dieri.p1 = p1;
	dieri.p2 = p2;
	dieri.lock2 = lock2;
	dieri.lock1 = lock1;


	
	pthread_create(& dieri.p1, NULL, routine, &i[0]);  // 42
	pthread_create(& dieri.p2, NULL, routine, &i[1]); // 92110
	pthread_join(dieri.p1, NULL); 
	pthread_join(dieri.p2, NULL); 
}