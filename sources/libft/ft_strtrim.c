/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:33:36 by vkostand          #+#    #+#             */
/*   Updated: 2024/02/03 17:55:49 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_match(char c, char const *str)
{
	int	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

/*char	*ft_strtrim(char const *s1, char const *set)
{
 	 char	*s1copy;
 	int		left;
 	int		right;
 	 int		i;

 	if (!s1)
 		return (NULL);
 	left = 0;
 	 i = 0;
	while (s1 && char_match(set, s1[left]))
 		left++;
 	right = ft_strlen(s1) - 1;
 	while (s1 && char_match(set, s1[right]))
 		right--;
 	 s1copy = (char *)malloc(sizeof(char) * (right - left + 2));
 	 if (!s1copy)
 	 	return (NULL);
		while (left <= right)
 	 {
 	 	s1copy[i++] = s1[left++];
 	 }
     if (left < right)
 		return (ft_strdup(""));
	// s1copy[i] = '\0';
	return (ft_substr(s1, left, (right - left + 1)));
}*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && char_match(s1[start], set))
		start++;
	while (end > 0 && char_match(s1[end], set))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(s1, start, (end - start + 1)));
}
