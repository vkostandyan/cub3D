/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:46:33 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/25 17:08:13 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void parse(int argc, char **argv)
{
    t_parse data;

    ft_bzero(&data, sizeof(data));
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