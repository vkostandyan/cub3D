/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:20 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/25 18:14:30 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "get_next_line.h"
#include "libft.h"

# define ARG_ERR "\033[1;31mInvalid number of arguments!\033[0m\n"
# define FILE_NAME_ERR "\033[1;31mInvalid file name!\033[0m\n"
# define FILE_OPEN_ERR "\033[1;31mCan't open file!\033[0m\n"
# define CHAR_ERR "\033[1;31mInvalid char in the map!\033[0m\n"
# define PLAYER_ERR "\033[1;31mMap must contain 1 player!\033[0m\n"

typedef struct s_parse
{
    char		**map;
    char		*north;
	char		*west;
	char		*east;
	char		*south;
    int			ceiling_color;
	int			floor_color;
}               t_parse;

void parse(int argc, char **argv);

void	send_error(char *str);

#endif