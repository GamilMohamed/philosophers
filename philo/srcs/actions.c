/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:28:11 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 02:50:55 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
