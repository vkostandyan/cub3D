/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:47:55 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/10 19:34:52 by kgalstya         ###   ########.fr       */
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
			{
				if (!data->map[i][j + 1] || !data->map[i][j - 1] || !data->map[i
					- 1][j] || !data->map[i + 1][j] || data->map[i][j
					+ 1] == ' ' || data->map[i][j - 1] == ' ' || data->map[i
					- 1][j] == ' ' || data->map[i + 1][j] == ' ')
				{
					clean_parsing_data(data);
					send_error("Map must be surrounded by walls\n");
				}
			}
			j++;
		}
		i++;
	}
	(void)data;
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
		if (player > 1)
		{
			clean_parsing_data(data);
			free_and_set_null(map);
			send_error("Map must contain 1 player\n");
		}
		i++;
	}
	if (player == 0)
	{
		clean_parsing_data(data);
		free_and_set_null(map);
		send_error("Map must contain 1 player\n");
	}
}

void	check_empty_lines(t_parse *data, char *map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		flag = 0;
		if (map[i] == '\n')
			i++;
		while (map[i] && map[i] != '\n')
		{
			if (map[i] == '1' || map[i] == '0' || map[i] == 'N'
				|| map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
				flag = 1;
			i++;
		}
		if (flag == 0)
		{
			free_and_set_null(map);
			clean_parsing_data(data);
			send_error("Empty line in the map\n");
		}
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
