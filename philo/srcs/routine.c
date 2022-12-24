/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:27:27 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 02:51:39 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	unlock(t_phil *phil)
{
	if (phil->left)
		pthread_mutex_unlock(phil->leftfork);
	if (phil->right)
		pthread_mutex_unlock(phil->rightfork);
	return (1);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->index % 2)
		usleep_(phil->timetoeat / 10, phil);
	while (1)
	{
		if (phil->goinfre && phil->data->nbphils % 2)
			usleep_(phil->timetodie * 0.25, phil);
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
