/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 04:03:31 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/09 14:39:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1char;
	char	*s2char;
	size_t	i;

	s1char = (char *)s1;
	s2char = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1char[i] != s2char[i])
			return ((unsigned char)s1char[i] - (unsigned char)s2char[i]);
		i++;
	}
	return (0);
}
