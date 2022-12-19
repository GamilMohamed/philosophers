/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:20 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/19 06:17:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "get_next_line.h"
# include "libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;93m"
# define MAGENTA "\033[0;95m"
# define BRED "\033[0;41m"
# define BGREEN "\033[0;42m"
# define BBLUE "\033[0;44m"
# define BYELLOW "\033[0;103m"
# define BMAGENTA "\033[0;105m"

typedef struct t_data
{
	int				ac;
	int				nbphils;
	pthread_mutex_t	*m_nbforks;
	int				nbforks;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	pthread_mutex_t	print;
	int				nbmaxeat;
}					t_data;

typedef struct t_phil
{
	int				index;
	pthread_t		*phils;
	pthread_mutex_t	leftfork;
	pthread_mutex_t	rightfork;
}					t_phil;

typedef struct t_all
{
	t_data			*data;
	t_phil			*phil;
}					t_all;

/*	MAIN.C			*/
void				*routine(void *arg);
/*	MISC.C			*/
void				ft_error(t_all *all, char *function, char *reason);
/*	INIT.C			*/
void				init(t_all *all, int ac, char **av);
void				print_struct(t_all all);
void				init_datas(t_all *all);
void				init_philos(t_all *all, t_data *data, t_phil *phil);

#endif