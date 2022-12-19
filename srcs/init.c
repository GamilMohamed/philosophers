/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:44:30 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/19 06:14:43 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(t_all *all, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		exit(1);
	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) < 0)
			exit(1);
	}
	all -> data -> ac = ac;
	all -> data -> nbphils = ft_atoi(av[1]);
	all -> data -> nbforks = all -> data -> nbphils;
	all -> data -> timetodie = ft_atoi(av[2]);
	all -> data -> timetoeat = ft_atoi(av[3]);
	all -> data -> timetosleep = ft_atoi(av[4]);
	all -> phil -> index = 1;
	if (ac > 5)
		all -> data -> nbmaxeat = ft_atoi(av[5]);
}

void	print_struct(t_all all)
{
	ft_printf("nbphils\t\t%m[%i\t👓]%0\n", all.data -> nbphils);
	ft_printf("nbforks\t\t%y[%i\t🍴]%0\n", all.data -> nbforks);
	ft_printf("timetodie\t%g[%i\t🥀]%0\n", all.data -> timetodie);
	ft_printf("timetoeat\t%g[%i\t🥘]%0\n", all.data -> timetoeat);
	ft_printf("timetosleep\t%g[%i\t💤]%0\n", all.data -> timetosleep);
	if (all.data -> ac > 5)
		ft_printf("nbmaxeat\t%r[%i\t❌]%0\n", all.data -> nbmaxeat);
}

void	init_philos(t_all *all, t_data *data, t_phil *phil)
{
	int i = -1;
	data -> m_nbforks = malloc(sizeof(pthread_mutex_t) * data -> nbphils + 1);
	if (!data -> m_nbforks)
		exit(1);
	while (++i < data -> nbphils)
		if (pthread_mutex_init(data -> m_nbforks, NULL) != 0)
			ft_error(all, "init.c (init_philos)", "mutex failed");
	if (pthread_mutex_init(& data -> print, NULL) != 0)
		ft_error(all, "init.c (init_philos)", "mutex print");
	i = -1;
	phil -> phils = malloc(sizeof(pthread_t) * data -> nbphils);
	while (++i < data -> nbphils)
		pthread_create(& phil -> phils[i], NULL, &routine, all);
	i = -1;
	while (++i < data -> nbphils)
		pthread_join(phil -> phils[i], NULL);
}