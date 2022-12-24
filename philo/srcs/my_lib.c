/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 02:04:27 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/24 02:56:04 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!*needle)
		return ((char *)(haystack));
	if (len <= 0)
		return (NULL);
	while ((haystack[i]) && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] == haystack[i + j] && i + j < len)
		{
			j++;
			if (!needle[j])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	y;
	int	res;

	i = 0;
	y = 1;
	res = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (-1);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res * y);
}
