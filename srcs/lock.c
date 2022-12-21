/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:53:22 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/21 06:01:48 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

ft_locknbool(t_all *all, pthread_mutex_t *lock, bool turn, int z)
{
	if (turn == 1)
	{
		if (pthread_mutex_lock(lock) != 0)
		{

		}

	}

}