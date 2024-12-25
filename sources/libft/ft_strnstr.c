/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:48:12 by vkostand          #+#    #+#             */
/*   Updated: 2024/02/01 20:00:12 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[j])
		{
			while ((haystack[i + j] == needle[j]) && i + j < len)
			{
				if (needle[j + 1] == '\0')
				{
					return ((char *)haystack + i);
				}
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
