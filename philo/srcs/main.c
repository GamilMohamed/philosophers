/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:18:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 01:55:30 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
