/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:40:56 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/09 18:17:26 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (src[i] && (i < dstsize - dstlen - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

// #include <bsd/string.h>

// int main()
// {
// 	char *test;
// 	test = malloc(30);

// 	int i = 0;
// 	while (i < 15)
// 		test[i++] = 'p';
// 	char *testo;
// 	testo = malloc(30);

// 	i = 0;
// 	while (i < 15)
// 		testo[i++] = 'p';
// 	ft_strlcat(test, testo, 15);
// 	strlcat(test, testo, 15);
// }