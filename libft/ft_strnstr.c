/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:42:10 by dleaves           #+#    #+#             */
/*   Updated: 2021/08/22 17:42:12 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			n_len;
	size_t			j;
	size_t			i;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	n_len = ft_strlen(needle);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (i + j < len && needle[j] == haystack[i + j])
		{
			j++;
			if (j == n_len)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
