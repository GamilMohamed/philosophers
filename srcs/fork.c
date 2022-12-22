/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 02:39:19 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/22 09:37:14 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	takeright(t_phil *phil)
{
	// if (is_dead(phil))
	// 	return (1);
	pthread_mutex_lock(phil->rightfork);
	if (show(phil, "has taken a fork"))
	{
		// printf("FUCK ME C BUGGGGGG %i\n", phil->index + 1);
		pthread_mutex_unlock(phil->rightfork);
		return (1);
	}
	return (0);
}

int	takeleft(t_phil *phil)
{
	pthread_mutex_lock(phil->leftfork);
	if (show(phil, "has taken a fork"))
	{
		// printf("FUCK ME C SECOND BUGGGGGG %i\n", phil->index + 1);
		pthread_mutex_unlock(phil->leftfork);
		return (1);
	}
	return (0);
}

int	takefork(t_phil *phil)
{
	if (phil->index != phil -> data -> nbphils - 1)
	{ //impair
		// if (is_dead(phil))
		// 	return (1);
		if (takeright(phil))
			return (1);
		if (takeleft(phil))
			return (1);
	}
	else
	{ //pair
		// if (is_dead(phil))
		// 	return (1);
		if (takeleft(phil))
			return (1);
		if (takeright(phil))
			return (1);
	}
	return (0);
}
