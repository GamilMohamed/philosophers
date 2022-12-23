/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/23 22:01:35 by mgamil           ###   ########.fr       */
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
			pthread_mutex_lock(&dead->data->shield);
			time = gettime() - convertoms(dead->data->phil[i].var);
			pthread_mutex_unlock(&dead->data->shield);
			if (time > dead->data->timetodie)
			{
				pthread_mutex_lock(&dead->data->deathchecker);
				dead->data->death = 1;
				pthread_mutex_unlock(&dead->data->deathchecker);
				pthread_mutex_lock(&dead->data->print);
				printf("%s[%li] %s%i%s died%s\n", RED, gettime()
						- dead->data->global, colorint(i + 1), i + 1, RESET,
						RESET);
				pthread_mutex_unlock(&dead->data->print);
				return (NULL);
			}
			pthread_mutex_lock(&dead->data->condition);
			if (dead->data->nbmaxeat == 0)
			{
				pthread_mutex_lock(&dead->data->deathchecker);
				dead->data->death = 1;
				pthread_mutex_unlock(&dead->data->deathchecker);
				pthread_mutex_unlock(&dead->data->condition);
				return (NULL);
			}
			pthread_mutex_unlock(&dead->data->condition);
		}
	}
	return (NULL);
}

int	unlock(t_phil *phil)
{
	if (phil->left)
		pthread_mutex_unlock(phil->leftfork);
	if (phil->right)
		pthread_mutex_unlock(phil->rightfork);
	return (1);
}
int	is_dead(t_phil *phil)
{
	int	death;

	pthread_mutex_lock(&phil->data->deathchecker);
	death = phil->data->death;
	pthread_mutex_unlock(&phil->data->deathchecker);
	if (death)
		return (1);
	return (0);
}

int	show(t_phil *phil, char *what)
{
	pthread_mutex_lock(&phil->data->print);
	if (is_dead(phil))
	{
		pthread_mutex_unlock(&phil->data->print);
		return (1);
	}
	printf("[%li] %s%i %s%s%s\n", gettime() - phil->data->global,
			colorint(phil->index + 1), phil->index + 1, color(what), what,
			RESET);
	pthread_mutex_unlock(&phil->data->print);
	return (0);
}

int	starteating(t_phil *phil)
{
	pthread_mutex_lock(&phil->data->shield);
	if (gettimeofday(&phil->var, NULL))
		return (1);
	pthread_mutex_unlock(&phil->data->shield);
	if (show(phil, "is eating"))
		return (1);
	else
	{
		phil->goinfre++;
		pthread_mutex_lock(&phil->data->condition);
		phil->data->nbmaxeat--;
		pthread_mutex_unlock(&phil->data->condition);
		usleep_(phil->timetoeat, phil);
	}
	phil -> left = 0;
	pthread_mutex_unlock(phil->leftfork);
	phil -> right = 0;
	pthread_mutex_unlock(phil->rightfork);
	return (0);
}

int	startsleeping(t_phil *phil)
{
	if (show(phil, "is sleeping"))
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
		if (phil->goinfre && phil->data->nbphils % 2)
			usleep_(phil->timetodie * 0.3, phil);
		if (takefork(phil))
			break ;
		if (starteating(phil))
			break ;
		if (startsleeping(phil))
			break ;
	}
	unlock(phil);
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
		pthread_mutex_destroy(&all.m_nbforks[i]);
	free(all.m_nbforks);
	free(all.phil);
}
