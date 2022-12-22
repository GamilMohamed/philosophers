/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/22 09:33:56 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *arg)
{
	t_dead	*dead;
	int		i;
	long	time;

	dead = (t_dead *)arg;
	while (1)
	{
		i = -1;
		while (++i < dead->data->nbphils)
		{
			pthread_mutex_lock(&dead->data->checker[i]);
			time = gettime() - convertoms(dead->data->phil[i].var);
			pthread_mutex_unlock(&dead->data->checker[i]);
			if (time > dead->data->timetodie)
			{
				printf("%s%li %i died%s\n", RED, gettime()
						- dead->data->global, i + 1, RESET);
				for (int j = 0; j < dead->data->nbphils; j++)
					pthread_mutex_lock(&dead->data->checker[j]);
				dead->data->death = 1;
				for (int j = 0; j < dead->data->nbphils; j++)
					pthread_mutex_unlock(&dead->data->checker[j]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	is_dead(t_phil *phil)
{
	pthread_mutex_lock(&phil->data->checker[phil->index]);
	if (phil->data->death)
	{
		pthread_mutex_unlock(&phil->data->checker[phil->index]);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->checker[phil->index]);
	return (0);
}

int	show(t_phil *phil, char *what)
{
	pthread_mutex_lock(&phil->data->print);
	if (is_dead(phil))
	{
		// printf("[%li] Phil[%i] FAILED while ->%s<- \n", gettime() - phil->data->global,
				// phil->index + 1, what);
		pthread_mutex_unlock(&phil->data->print);
		return (1);
	}
	printf("%li %i %s%s%s\n", gettime() - phil->data->global,
			phil->index + 1, color(what), what, RESET);
	pthread_mutex_unlock(&phil->data->print);
	return (0);
}

int	starteating(t_phil *phil)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phil->data->shield);
	if (gettimeofday(&phil->var, NULL))
		return (1);
	pthread_mutex_unlock(&phil->data->shield);
	if (show(phil, "is eating"))
		return (1);
	else
		usleep_(phil->timetoeat, phil);
	pthread_mutex_unlock(phil->leftfork);
	pthread_mutex_unlock(phil->rightfork);
	return (ret);
}

int	startsleeping(t_phil *phil)
{
	if (show(phil, "is startsleeping"))
		return (1);
	if (usleep_(phil->timetosleep, phil))
		return (1);
	if (show(phil, "is thinking"))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->index % 2 == 0)
		usleep_(phil->timetoeat / 10, phil);
	while (1)
	{
		if (is_dead(phil))
			break ;
		if (takefork(phil))
			break ;
		if (starteating(phil))
			break ;
		if (startsleeping(phil))
			break ;
		// show(phil, "did a loop");
	}
	// show(phil, "has quit");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_all	all;
	int		i;

	memset(&all, 0, sizeof(t_all));
	if (init_all(&all, ac, av))
		return (1);
	i = -1;
	while (++i < all.nbphils)
	{
		pthread_mutex_destroy(&all.m_nbforks[i]);
		pthread_mutex_destroy(&all.checker[i]);
		free(&all.phil[i]);
	}
}
