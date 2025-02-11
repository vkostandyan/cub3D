/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:29:56 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/10 17:56:10 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 3 functions

#include "parsing.h"

int	is_empty_line(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] && char_match(str[i], set))
		i++;
	if (str[i])
		return (0);
	return (1);
}

t_type	check_type(char *str, t_parse *data, int fd, t_type type, int status)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (EMPTY);
	if (ft_strstr(str + i, "NO"))
		return (NORTH);
	if (ft_strstr(str + i, "SO"))
		return (SOUTH);
	if (ft_strstr(str + i, "WE"))
		return (WEST);
	if (ft_strstr(str + i, "EA"))
		return (EAST);
	if (ft_strstr(str + i, "F"))
		return (FLOOR);
	if (ft_strstr(str + i, "C"))
		return (CEILING);
	printf("blabla\n");
	decide_error(str, type, status);
	clean_parsing_data(data);
	close(fd);
	free_and_set_null(str);
    // system("leaks cub3D");
	exit(1);
	return (NOT_VALID);
}

void free_and_set_null(char *str)
{
	if(str)
	{
		free(str);
		str = NULL;
	}
}

void clean_parsing_data(t_parse *data)
{
    free_array(data->map);
	data->map = NULL;
    if(data->north)
		free_and_set_null(data->north);
    if(data->south)
		free_and_set_null(data->south);
    if(data->east)
		free_and_set_null(data->east);
    if(data->west)
		free_and_set_null(data->west);
	close(data->east_fd);
	close(data->south_fd);
	close(data->north_fd);
	close(data->west_fd);
}

char	*ft_join(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	if (i != 0)
		s[i++] = '\n';
	while (s2[j] != '\0')
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

void	check_name(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		send_error(ARG_ERR);
	len = ft_strlen(argv[1]) - 4;
	if (len <= 0 || ft_strncmp(".cub", argv[1] + len, 4) != 0)
		send_error(FILE_NAME_ERR);
}
