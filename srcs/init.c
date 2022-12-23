/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:44:30 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/23 02:42:51 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_struct(t_all *all, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_printf("%r./philo [nb_phils][t.die][t.eat][t.sleep]%0\n"));
	i = 0;
	while (++i < ac)
		if (ft_atoi(av[i]) < 0)
			return (1);
	all->nbphils = ft_atoi(av[1]);
	all->timetodie = ft_atoi(av[2]);
	all->timetoeat = ft_atoi(av[3]);
	all->timetosleep = ft_atoi(av[4]);
	all->death = 0;
	all->nbmaxeat = 2147483647;
	if (ac > 5)
		all->nbmaxeat = ft_atoi(av[5]);
	return (0);
}

static int	init_philos(t_all *all)
{
	int	i;

	i = -1;
	all->m_nbforks = malloc(sizeof(pthread_mutex_t) * all->nbphils);
	if (!all->m_nbforks)
		return (1);
	while (++i < all->nbphils)
		if (pthread_mutex_init(& all->m_nbforks[i], NULL))
			return (ft_error(all, "init.c (init_philos)", i, 1));
	if (pthread_mutex_init(&all->shield, NULL))
		return (ft_error(all, "init.c (init_philos)", -1, 1));
	if (pthread_mutex_init(&all->condition, NULL))
		return (ft_error(all, "init.c (init_philos)", -1, 1));
	/**/
	if (pthread_mutex_init(&all->deathchecker, NULL))
		return (ft_error(all, "init.c (init_philos)", -1, 1));
	/**/
	return (0);
}

static int	init_tabstruct(t_all *all)
{
	int	i;

	i = -1;
	all->phil = malloc(sizeof(t_phil) * all->nbphils);
	memset(all->phil, 0, sizeof(t_phil) * all ->nbphils);
	if (!all->phil)
		return (ft_error(all, "init.c (init_tabstruct)", -1, 2));
	i = -1;
	while (++i < all->nbphils)
	{
		all->phil[i].data = all;
		all->phil[i].timetodie = all->timetodie;
		all->phil[i].timetoeat = all->timetoeat;
		all->phil[i].timetosleep = all->timetosleep;
		all->phil[i].nbmaxeat = all->nbmaxeat;
		all->phil[i].leftfork = &all->m_nbforks[i];
		all->phil[i].index = i;
		if (i == all->nbphils - 1)
			all->phil[i].rightfork = &all->m_nbforks[0];
		else
			all->phil[i].rightfork = &all->m_nbforks[i + 1];
		if (gettimeofday(&all->phil[i].var, NULL) == -1)
			return (ft_error(all, "init.c (init_tabstruct)", -1, 3));
	}
	return (0);
}

static int	init_threads(t_all *all, t_phil *phil)
{
	int		i;
	t_dead	dead;

	memset(&dead, 0, sizeof(t_dead));
	dead.data = all;
	dead.phil = phil;
	i = -1;
	if (pthread_mutex_init(& dead.protector, NULL))
		return (ft_error(all, "protector (init_threads)", -1, 1));
	all->global = gettime();
	if (pthread_create(&dead.stalker, NULL, &checker, &dead) != 0)
		return (ft_error(all, "stalker (init_threads)", -1, 3));
	while (++i < all->nbphils)
		if (pthread_create(&phil[i].phils, NULL, &routine, &phil[i]) != 0)
			return (ft_error(all, "create phil (init_threads)", -1, 3));
	i = -1;
	while (++i < all->nbphils)
		if (pthread_join(phil[i].phils, NULL) != 0)
			return (ft_threadserror(all, "join (init_threads)", i) != 0);
	if (pthread_join(dead.stalker, NULL) != 0)
		return (ft_threadserror(all, "join2 (init_threads)", i) != 0);
	
	return (0);
}

int	init_all(t_all *all, int ac, char **av)
{
	if (init_struct(all, ac, av))
		return (1);
	if (init_philos(all))
		return (1);
	if (init_tabstruct(all))
		return (1);
	if (init_threads(all, all->phil))
		return (1);
	return (0);
}
