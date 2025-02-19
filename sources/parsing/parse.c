/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:46:33 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:49:12 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	check_and_save_textures(char *str, t_parse *data, int fd)
{
	int	type;
	int	status;

	type = check_type(str);
	status = 0;
	if (type == NOT_VALID)
	{
		decide_error(str, type, status);
		clean_parsing_data(data);
		close(fd);
		free_and_set_null(str);
		exit(1);
	}
	status = save_textures(data, str, type);
	if (status != SUCCESS)
	{
		decide_error(str, type, status);
		free_and_set_null(str);
		close(fd);
		clean_parsing_data(data);
		exit(1);
	}
}

static void	read_textures(t_parse *data, int fd)
{
	int		not_empty_line;
	char	*str;

	not_empty_line = 0;
	while (not_empty_line < 6)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (is_empty_line(str, " \n\t\v"))
		{
			free_and_set_null(str);
			continue ;
		}
		check_and_save_textures(str, data, fd);
		free_and_set_null(str);
		not_empty_line++;
	}
	if (not_empty_line != 6)
		send_error("Not enough textures\n");
}

t_parse	parse(int argc, char **argv)
{
	t_parse	data;
	int		fd;

	ft_bzero(&data, sizeof(data));
	check_name(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		send_error(FILE_OPEN_ERR);
	read_textures(&data, fd);
	read_and_parse_map(&data, fd);
	get_player_position(&data);
	get_map_height_and_width(&data);
	return (data);
	(void)argc;
	(void)argv;
	(void)data;
}
