/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 02:52:21 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/09 14:39:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*srcchar;
	char		*dstchar;
	size_t		i;

	i = 0;
	srcchar = (char *)src;
	dstchar = (char *)dst;
	if (!srcchar && !dstchar)
		return (NULL);
	if (dst > src)
		while (i++ < len)
			dstchar[len - i] = srcchar[len - i];
	else
	{
		i = -1;
		while (len - ++i > 0)
			dstchar[i] = srcchar[i];
	}
	return (dst);
}
