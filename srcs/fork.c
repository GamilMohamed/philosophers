/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 02:39:19 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/20 22:51:36 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	takeright(t_phil *phil)
{
	pthread_mutex_lock(phil -> rightfork);
	show(phil, "has taken right fork");
	return (0);
}

int	takeleft(t_phil *phil)
{
	pthread_mutex_lock(phil -> leftfork);
	show(phil, "has taken left fork");
	return (0);
}

int	takefork(t_phil *phil)
{
	if (phil -> index % 2)
	{ //impair
		takeright(phil);
		takeleft(phil);
	}
	else
	{ //pair
		takeleft(phil);
		takeright(phil);
	}
	return (0);
}
