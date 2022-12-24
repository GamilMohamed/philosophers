/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:50:36 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 02:54:30 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	checkcondition(t_dead *dead)
{
	pthread_mutex_lock(&dead->data->condition);
	if (dead->data->nbmaxeat == 0)
	{
		pthread_mutex_lock(&dead->data->deathchecker);
		dead->data->death = 1;
		pthread_mutex_unlock(&dead->data->deathchecker);
		pthread_mutex_unlock(&dead->data->condition);
		return (1);
	}
	pthread_mutex_unlock(&dead->data->condition);
	return (0);
}

void	*locknprint(pthread_mutex_t *print, int index, long time)
{
	pthread_mutex_lock(print);
	printf("%s[%li] %s%i died%s\n", RED, gettime() - time,
		colorint(index + 1), index + 1, RESET);
	pthread_mutex_unlock(print);
	return (NULL);
}

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
				return (locknprint(&dead->data->print, i, dead->data->global));
			}
			if (checkcondition(dead))
				return (NULL);
		}
	}
	return (NULL);
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
