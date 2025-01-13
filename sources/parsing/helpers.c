/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:29:56 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/13 15:26:14 by vkostand         ###   ########.fr       */
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
	decide_error(str, type, status);
	clean_parsing_data(data);
	close(fd);
	free_and_set_null(str);
	exit(1);
	return (NOT_VALID);
}

void free_and_set_null(char *str)
{
	free(str);
	str = NULL;
}

void clean_parsing_data(t_parse *data)
{
    free_array(data->map);
    if(data->north)
		free_and_set_null(data->north);
    if(data->south)
		free_and_set_null(data->south);
    if(data->east)
		free_and_set_null(data->east);
    if(data->west)
		free_and_set_null(data->west);
}
