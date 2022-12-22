# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
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

char *gnl(int fd)
{
	char *str = malloc(1000), *cpy = str;
	while (read(fd, cpy, 1) > 0 && *cpy++ != '\n');
	return (cpy > str) ? (*cpy = 0, str) : (free(str), NULL);
}
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
	return (NULL);
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

	int fd = open("text", O_RDONLY);
	char *s;
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);
	s = gnl(fd);
	printf("%s", s);
	free(s);

	s = gnl(fd);
	printf("%s", s);
	free(s);
	// pthread_create(& dieri.p1, NULL, routine, &i[0]);  // 42
	// pthread_create(& dieri.p2, NULL, routine, &i[1]); // 92110
	// pthread_join(dieri.p1, NULL); 
	// pthread_join(dieri.p2, NULL); 
}