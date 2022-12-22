/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:46:13 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/22 04:43:59 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) == -1)
		return (-1);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

long	convertoms(struct timeval var)
{
	return (var.tv_sec * 1000 + var.tv_usec / 1000);
}

void	usleep_(long int duration, t_phil *phil)
{
	long int	start;
	long int	current;

	start = -1;
	start = gettime();
	if (start == -1)
		return ;
	else
	{
		while (1)
		{
			current = gettime() - start;
			if (current >= duration)
				break ;
			if (duration - current > 1000)
				usleep(100);
			else
				usleep((duration - current) / 10);
			if (is_dead(phil))
				break ;
		}
	}
}