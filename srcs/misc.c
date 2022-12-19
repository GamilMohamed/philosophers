/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 01:51:15 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/19 04:03:05 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(t_all *all, char *function, char *reason)
{
	ft_printf("failed in:%s\n", function);
	ft_printf("while:%s\n", reason);
	free(all->data->m_nbforks);
	free(all->phil->phils);
	exit (1);
}
