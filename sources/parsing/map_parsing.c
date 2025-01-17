/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:47:55 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/17 15:55:37 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void check_chars(t_parse *data, char *map)
{
    int i;
    int player;

    i = 0;
    player = 0;
    while(map[i])
    {
        if(map[i] == 'N' || map[i] == 'S' 
            || map[i] == 'E' || map[i] == 'W')
            player++;
        else if(map[i] != '0' && map[i] != '1' 
            && map[i] != '\n' && map[i] != ' ')
        {
                clean_parsing_data(data);
                free_and_set_null(map);
                send_error("Forbidden character in the map\n");
        }
        if(player > 1)
        {
            clean_parsing_data(data);
            free_and_set_null(map);     
            send_error("Map must contain 1 player\n");
        }
        i++;
    }
    if(player == 0)
    {
        clean_parsing_data(data);
        free_and_set_null(map); 
        send_error("Map must contain 1 player\n");
    }
}
