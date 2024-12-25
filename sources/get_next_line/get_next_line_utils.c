/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:02:48 by vkostand          #+#    #+#             */
/*   Updated: 2024/05/24 14:30:29 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_join(char *buffer, char *line)
{
	char	*temp;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	temp = gnl_strjoin(buffer, line);
	return (temp);
}

char	*gnl_strjoin(char *buffer, char *line)
{
	char	*s;
	int		i;
	int		j;

	if (!buffer || !line)
		return (NULL);
	s = (char *)malloc(sizeof(char)
			* (gnl_strlen(buffer) + gnl_strlen(line) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[i] != '\0')
	{
		s[i] = buffer[i];
		i++;
	}
	while (line[j] != '\0')
	{
		s[i + j] = line[j];
		j++;
	}
	s[i + j] = '\0';
	free(buffer);
	return (s);
}
