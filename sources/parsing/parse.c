/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:46:33 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/13 15:51:34 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 3 functions

#include "parsing.h"

static void	check_name(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		send_error(ARG_ERR);
	len = ft_strlen(argv[1]) - 4;
	if (len <= 0 || ft_strncmp(".cub", argv[1] + len, 4) != 0)
		send_error(FILE_NAME_ERR);
}

static void read_textures(t_parse *data, int fd)
{
    int not_empty_line;
    char *str;
    int type;
    int status;

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
        if(status != SUCCESS)
        {
            decide_error(str, type, status);
            free_and_set_null(str);
            close(fd);
            clean_parsing_data(data);
            system("leaks cub3D");
            exit(1);
        }
        free_and_set_null(str);
        not_empty_line++;
    }
    close(fd);
    if(not_empty_line != 6)
        send_error("\033[1;31mError\033[0m\nNot enough textures\n");
}

static void read_map(t_parse *data, int fd)
{
    // char *str;

    // while(1)
    // {
    //     str
    // }
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
    read_map(&data, fd);
    clean_parsing_data(&data);
    (void)argc;
    (void)argv;
    (void)data;
}
