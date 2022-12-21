/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/21 06:06:34 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime2(struct timeval start)
{
	gettimeofday(&start, NULL);
	return (1000 * start.tv_sec + start.tv_usec / 1000);
}

void	*checker(void *arg)
{
	t_dead *dead;
	int i;

	dead = (t_dead *)arg;
	while (1)
	{
		i = -1;
		while (++i < dead -> data -> nbphils)
		{
			if (gettime2(dead -> data -> phil[i].var) - dead -> data -> global >= dead -> data -> timetodie)
			{
				printf("Phil[%i] is dead\n", i);
				exit(1);
			}
		}
	}
	return (NULL);
}

long	gettime(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (1000 * start.tv_sec + start.tv_usec / 1000);
}

int	is_dead(t_phil *phil)
{
	pthread_mutex_lock(& phil -> data -> shield);
	if (phil -> data -> death)
		return (1);
	pthread_mutex_unlock(& phil -> data -> shield);
	return (0);
}


int	show(t_phil *phil, char *what)
{
	pthread_mutex_lock(&phil -> data -> print);
	printf("[%li] Phil[%i] %s%s%s\n", gettime() - phil -> data -> global, phil -> index + 1,
				color(what), what, RESET);
	pthread_mutex_unlock(&phil -> data -> print);
	return (0);
}

int	starteating(t_phil *phil)
{
	show(phil, "is eating");
	if (!(--phil -> nbmaxeat))
	{
		show(phil, "sayer mon gars");
		//unlock mutexes;
		return (1);
	}
	pthread_mutex_lock(&phil -> data -> shield);
	if(gettimeofday(& phil -> var, NULL))
		return (1);
	printf("%i avant ->>>> %li\n", phil -> index, gettime2(phil->var) - phil -> data -> global);
	usleep(phil -> timetoeat * 1000);
	printf("%i apres ->>>> %li\n", phil -> index, gettime2(phil->var) - phil -> data -> global);
	show(phil, "vient de mettre a jour son temps");
	pthread_mutex_unlock(& phil -> data -> shield);
	pthread_mutex_unlock(phil -> leftfork);
	pthread_mutex_unlock(phil -> rightfork);
	return (0);
}

int	startsleeping(t_phil *phil)
{
	show(phil, "is sleeping");
	usleep(phil -> timetosleep * 1000);
	show(phil, "is thinking");
	return (0);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	
	phil = (t_phil *)arg;
	while (1)
	{
		if(takefork(phil))
			break ;
		if (starteating(phil))
			break ;
		if (startsleeping(phil))
			break ;
	}
	ft_printf("ok many\n");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_all	all;

	memset(&all, 0, sizeof(t_all));
	if(init_all(&all, ac, av))
		return (1);
}
