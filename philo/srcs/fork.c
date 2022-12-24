/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 02:39:19 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 01:55:43 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	takeright(t_phil *phil)
{
	pthread_mutex_lock(phil->rightfork);
	phil->right = 1;
	if (show(phil, "has taken a fork"))
		return (1);
	return (0);
}

int	takeleft(t_phil *phil)
{
	pthread_mutex_lock(phil->leftfork);
	phil->left = 1;
	if (show(phil, "has taken a fork"))
		return (1);
	return (0);
}

int	takefork(t_phil *phil)
{
	if (phil->index % 2)
	{
		if (takeright(phil))
			return (1);
		if (takeleft(phil))
			return (1);
	}
	else
	{
		if (takeleft(phil))
			return (1);
		if (phil->leftfork == phil->rightfork)
			return (1);
		if (takeright(phil))
			return (1);
	}
	return (0);
}
