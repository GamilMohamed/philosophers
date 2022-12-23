/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:20 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/23 01:59:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "get_next_line.h"
# include "libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
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

typedef struct t_phil	t_phil;

typedef struct t_all
{
	long int			global;
	t_phil				*phil;
	bool				death;
	int					nbphils;
	pthread_mutex_t		*checker;
	pthread_mutex_t		deathchecker;
	pthread_mutex_t		*m_nbforks;
	int					timetodie;
	int					timetoeat;
	int					timetosleep;
	int					nbmaxeat;
	pthread_mutex_t		print;
	pthread_mutex_t		shield;
}						t_all;

typedef struct t_phil
{
	struct timeval		var;
	t_all				*data;
	pthread_t			phils;
	int					index;
	int					timetodie;
	int					timetoeat;
	int					timetosleep;
	int					nbmaxeat;
	int					goinfre;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
}						t_phil;

typedef struct t_dead
{
	pthread_t			stalker;
	pthread_mutex_t		protector;
	t_phil				*phil;
	t_all				*data;

}						t_dead;

/*	MAIN.C			*/
void					*routine(void *arg);
int						show(t_phil *phil, char *what);
long					gettime(void);
void					*checker(void *arg);
int						is_dead(t_phil *phil);

/*	MISC.C			*/
int						ft_threadserror(t_all *all, char *function, int index);
int						ft_error(t_all *all, char *function, int index,
							int value);
char					*color(char *what);
/*	INIT.C			*/
int						init_all(t_all *all, int ac, char **av);
/*	FORK.C			*/
int						takeleft(t_phil *phil);
int						takeright(t_phil *phil);
int						takefork(t_phil *phil);
/*	TIME.C			*/
long					gettime(void);
long					convertoms(struct timeval var);
int					usleep_(long int duration, t_phil *phil);

#endif