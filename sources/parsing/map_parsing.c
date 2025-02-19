/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:47:55 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:34:15 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*read_map(int fd)
{
	char	*current_line;
	char	*result;
	char	*temp;
	char	*current_temp;

	result = "";
	while (1)
	{
		current_line = get_next_line(fd);
		if (!current_line)
			break ;
		temp = result;
		if (!is_empty_line(current_line, " \n\t\v"))
		{
			current_temp = ft_strtrim(current_line, " \n\t\v");
			result = ft_join(temp, current_temp);
			free(current_temp);
		}
		else
			result = ft_strjoin(temp, current_line);
		if (ft_strncmp(result, current_line, ft_strlen(result)) != 0)
			free(temp);
		free(current_line);
	}
	return (result);
}

void	check_walls_helper(t_parse *data, int i, int j)
{
	if (!data->map[i][j + 1] || (data->map[i][j + 1] && (data->map[i][j
				+ 1] == ' ' || data->map[i][j + 1] == '\n')))
	{
		clean_parsing_data(data);
		send_error("Map must be surrounded by walls\n");
	}
	if (j == 0 || !data->map[i][j - 1] || (data->map[i][j - 1]
			&& (data->map[i][j - 1] == ' ' || data->map[i][j - 1] == '\n')))
	{
		clean_parsing_data(data);
		send_error("Map must be surrounded by walls\n");
	}
	if (!data->map[i - 1] || !data->map[i + 1])
	{
		clean_parsing_data(data);
		send_error("Map must be surrounded by walls\n");
	}
	if (i == 0 || !data->map[i - 1][j] || (data->map[i - 1][j] && (data->map[i
				- 1][j] == ' ' || data->map[i - 1][j] == '\n')) || !data->map[i
		+ 1][j] || (data->map[i + 1][j] && (data->map[i + 1][j] == ' '
				|| data->map[i + 1][j] == '\n')))
	{
		clean_parsing_data(data);
		send_error("Map must be surrounded by walls\n");
	}
}

void	check_walls(t_parse *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
				check_walls_helper(data, i, j);
			j++;
		}
		i++;
	}
}

void	check_chars(t_parse *data, char *map)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
			player++;
		else if (map[i] != '0' && map[i] != '1' && map[i] != '\n'
			&& map[i] != ' ')
		{
			clean_parsing_data(data);
			free_and_set_null(map);
			send_error("Forbidden character in the map\n");
		}
		i++;
	}
	if (player != 1)
	{
		clean_parsing_data(data);
		free_and_set_null(map);
		send_error("Map must contain 1 player\n");
	}
}

void	read_and_parse_map(t_parse *data, int fd)
{
	char	*map;
	char	*temp;

	temp = read_map(fd);
	close(fd);
	map = ft_strtrim(temp, " \t\v\n");
	free_and_set_null(temp);
	check_empty_lines(data, map);
	check_chars(data, map);
	data->map = ft_split(map, '\n');
	free_and_set_null(map);
	if (!data->map)
	{
		clean_parsing_data(data);
		send_error("malloc error\n");
	}
	check_walls(data);
	(void)data;
	(void)fd;
}
