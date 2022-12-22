/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/22 05:43:07 by mgamil           ###   ########.fr       */
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
			time = gettime() - convertoms(dead->data->phil[i].var);
			pthread_mutex_unlock(&dead->data->checker[i]);
			if (time > dead->data->timetodie)
			{
				pthread_mutex_lock(&dead->data->print);
				printf("%s[%li] Phil[%i] is dead%s\n", RED, gettime()
						- dead->data->global, i + 1, RESET);
				pthread_mutex_unlock(&dead->data->print);
				pthread_mutex_lock(&dead->data->checker[i]);
				dead->data->death = 1;
				pthread_mutex_unlock(&dead->data->checker[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	is_dead(t_phil *phil)
{
	int	ret;

	pthread_mutex_lock(&phil->data->checker[phil->index]);
	ret = 0;
	if (phil->data->death)
		ret = 1;
	pthread_mutex_unlock(&phil->data->checker[phil->index]);
	return (ret);
}

int	show(t_phil *phil, char *what)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phil->data->print);
	if (!is_dead(phil))
		printf("[%li] Phil[%i] %s%s%s\n", gettime() - phil->data->global,
				phil->index + 1, color(what), what, RESET);
	else
		ret = -1;
	pthread_mutex_unlock(&phil->data->print);
	return (ret);
}

int	starteating(t_phil *phil)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phil->data->shield);
	if (gettimeofday(&phil->var, NULL))
		return (1);
	pthread_mutex_unlock(&phil->data->shield);
	if (show(phil, "is eating") == -1)
		return (1);
	else
		usleep_(phil->timetoeat, phil);
	pthread_mutex_unlock(phil->leftfork);
	pthread_mutex_unlock(phil->rightfork);
	return (ret);
}

int	startsleeping(t_phil *phil)
{
	show(phil, "is sleeping");
	usleep_(phil->timetosleep, phil);
	show(phil, "is thinking");
	return (0);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (1)
	{
		takefork(phil);
		starteating(phil);
		startsleeping(phil);
		if (is_dead(phil))
			break ;
	}
	show(phil, "has quit");
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
