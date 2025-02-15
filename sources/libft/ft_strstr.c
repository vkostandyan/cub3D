/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:36:18 by marvin            #+#    #+#             */
/*   Updated: 2024/12/28 21:36:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;

	if (!str)
		return (0);
	i = 0;
	if (*to_find == '\0')
		return (1);
	if (ft_strlen(str) < ft_strlen(to_find))
		return (0);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
