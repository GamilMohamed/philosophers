/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:20 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 02:11:29 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

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
	pthread_mutex_t		condition;
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
	bool				left;
	bool				right;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
}						t_phil;

typedef struct t_dead
{
	pthread_t			stalker;
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
char					*colorint(int n);
/*	INIT.C			*/
int						init_all(t_all *all, int ac, char **av);
/*	FORK.C			*/
int						takeleft(t_phil *phil);
int						takeright(t_phil *phil);
int						takefork(t_phil *phil);
/*	TIME.C			*/
long					gettime(void);
long					convertoms(struct timeval var);
int						usleep_2(long int duration, t_phil *phil);
int						usleep_(long int duration, t_phil *phil);
/*	ACTIONS.C		*/
int						starteating(t_phil *phil);
int						startsleeping(t_phil *phil);
/*	DEATH.C			*/
void					*checker(void *arg);
int						is_dead(t_phil *phil);
/*	MY_LIB.C		*/
char					*ft_strnstr(char const *haystack, char const *needle,
							size_t len);
size_t					ft_strlen(const char *str);
int						ft_atoi(const char *str);

#endif