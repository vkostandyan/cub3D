/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:47:55 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/16 21:17:42 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void check_chars(t_parse *data, char *map)
{
    int i;

    i = 0;
    while(map[i])
    {
        if(map[i] != '0' && map[i] != '1' && map[i] != 'N' && 
            map[i] != 'S' && map[i] != 'E' && map[i] != 'W' && 
            map[i] != '\n' && map[i] != ' ')
        {
            clean_parsing_data(data);
            free_and_set_null(map);       
            send_error("Forbidden character in the map\n");
        }
        i++;
    }
}
