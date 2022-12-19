/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/19 06:20:06 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

ssize_t	tm_gimme(struct timeval start)
{
	struct timeval	end;

	if (gettimeofday(&end, NULL) == -1)
		return (0);
	return ((1e3 * ((&end)->tv_sec - (&start)->tv_sec)) + (1e-3
			* ((&end)->tv_usec - (&start)->tv_usec)));
}

void	printtime(void)
{
	struct timeval	clock;

	if (gettimeofday(&clock, NULL) == -1)
		return ;
	printf("[%s%lld%s]", BMAGENTA, (clock.tv_sec * 1000LL + clock.tv_usec
				/ 1000), RESET);
}

// int	checkfork(t_all *all)
// {
// 	if (all->data->nbphils % 2 == 0)
// 		return (1);
// 	else
// 		return (2);
// }

void	*routine(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	pthread_mutex_lock(&all->data->print);
			printtime();
	printf("Philo n°%i\n", all->phil->index);
	// if (all->phil->)
	// if (checkfork(all) == 2)
	// {
	// 	if ((all->phil->index++ % 2) > 0)
	// 	{
	// 		printf("Philo n°%i has taken a fork\n", all->phil->index);
	// 	}
	// }
		all->phil->index++;
	pthread_mutex_unlock(&all->data->print);
	sleep(1);
	pthread_mutex_lock(&all->data->print);
	printtime();
	printf("Ending threads\n");
	pthread_mutex_unlock(&all->data->print);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_phil	phil;
	t_all	all;

	all.data = &data;
	all.phil = &phil;
	init(&all, ac, av);
	print_struct(all);
	init_philos(&all, &data, &phil);
}
