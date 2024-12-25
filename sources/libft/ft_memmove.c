/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:01:01 by vkostand          #+#    #+#             */
/*   Updated: 2024/01/24 19:50:17 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;

	if (!dst && !src)
		return (NULL);
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (src1 < dst1)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dst1[i] = src1[i];
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}
