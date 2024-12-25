/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:20 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/25 17:07:42 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "get_next_line.h"
#include "libft.h"

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

#endif