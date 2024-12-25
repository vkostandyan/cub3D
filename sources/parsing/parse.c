/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:46:33 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/25 22:55:24 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void parse(int argc, char **argv)
{
    t_parse data;
	int flag;

	flag = 0;
    ft_bzero(&data, sizeof(data));
	check_name(argc, argv);
	// while()
    (void)argc;
    (void)argv;
    (void)data;
}

// void parse(int argc, char **argv)
// {
//     (void)argc;
//     char *str;

//     int fd = open(argv[1], O_RDONLY);
//     if(fd == -1)
//         exit(1);
//     str = get_next_line(fd);
//     printf("%s\n", str);
//     free(str);
//     close(fd);
// }