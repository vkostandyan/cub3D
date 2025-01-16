/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:46:33 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/16 21:06:56 by vkostand         ###   ########.fr       */
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

static void read_textures(t_parse *data, int fd)
{
    int not_empty_line;
    char *str;
    int type;
    int status = 0;

    not_empty_line = 0;
    while(not_empty_line < 6)
    {
        str = get_next_line(fd);
        if(!str)
            break ;
        if(is_empty_line(str, " \n\t\v"))
        {
            free_and_set_null(str);
            continue;
        }
        type = check_type(str, data, fd, type, status);
        status = save_textures(data, str, type);
        free_and_set_null(str);
        if(status != SUCCESS)
        {
            decide_error(str, type, status);
            close(fd);
            clean_parsing_data(data);
            system("leaks cub3D");
            exit(1);
        }
        not_empty_line++;
    }
    if(not_empty_line != 6)
        send_error("\033[1;31mError\033[0m\nNot enough textures\n");
}

static void parse_map(t_parse *data)
{
    (void)data;
}

static void read_and_parse_map(t_parse *data, int fd)
{
    char *map;
    char *temp;

    temp = read_map(fd);
    map = ft_strtrim(temp, " \t\v\n");
    free_and_set_null(temp);
    check_chars(data, map);
    data->map = ft_split(map, '\n');
    free_and_set_null(map);
    if(!data->map)
    {
        clean_parsing_data(data);
        send_error("malloc error\n");
    }
    parse_map(data);
    (void)data;
    (void)fd;
}

void parse(int argc, char **argv)
{
    t_parse data;
    int fd;

    ft_bzero(&data, sizeof(data));
    check_name(argc, argv);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
		send_error(FILE_OPEN_ERR);
    read_textures(&data, fd);
    read_and_parse_map(&data, fd);
    clean_parsing_data(&data);
    (void)argc;
    (void)argv;
    (void)data;
}
