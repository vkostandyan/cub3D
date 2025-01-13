/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:13:03 by marvin            #+#    #+#             */
/*   Updated: 2024/12/28 23:13:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_digit(char **split)
{
    int i;
    i = 0;
    while(split[0][i])
    {
        if(!ft_isdigit(split[0][i]))
            return(0);
        i++;
    }
    i = 0;
    while(split[1][i])
    {
        if(!ft_isdigit(split[1][i]))
            return(0);
        i++;
    }
    i = 0;
    while(split[2][i] && split[2][i + 1])
    {
        if(!ft_isdigit(split[2][i]))
            return(0);
        i++;
    }
    return (1);
}

int get_color2(char **split)
{
    int red;
    int green;
    int blue;

    if(ft_strlen(split[0]) > 10 || ft_strlen(split[1]) > 10 || ft_strlen(split[2]) > 10)
    {
        free_array(split);
        return (INVALID_RANGE);
    }
    red = ft_atoi(split[0]);
    green = ft_atoi(split[1]);
    blue = ft_atoi(split[2]);
    free_array(split);
    if(red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        return(INVALID_RANGE);
    return (red * 256 * 256 + green * 256 + blue);
}

int get_color(char *str)
{
    char **split;
    int len;
    if((str[0] && str[0] == ',') || (str[ft_strlen(str) - 1] && str[ft_strlen(str) - 1] == ','))
        return (EDGE_COMMA);
    if(ft_strstr(str, ",,"))
        return (DOUBLE_COMMA);
    split = ft_split(str, ',');
    if(!split)
        return (MALLOC);
    len = count_array_len(split);
    if(count_array_len(split) != 3)
    {
        free_array(split);
        return(len > 3 ? TOO_MANY_VALUES : TOO_FEW_VALUES);
    }
    if(!check_digit(split))
    {
        free_array(split);
        return (INVALID_COLOR_ARGUMENTS);
    }
    return (get_color2(split));
}

int set_floor(t_parse *data, char *str)
{
    char **split;
    int len;
    if(data->floor_color)
        return (DOUBLICATE);
    split = ft_split(str, ' ');
    if(!split)
        return(MALLOC);
    len = count_array_len(split);
    if(len != 2)
    {
        free_array(split);
        return(len > 2 ? TOO_MANY_VALUES : TOO_FEW_VALUES);
    }
    if(ft_strcmp("F", split[0]))
    {
        free_array(split);
        return (INVALID_KEY);
    }
    data->floor_color = get_color(split[1]);
    free_array(split);
    if(data->floor_color < 0)
        return (data->floor_color);
    return (SUCCESS);
}

int set_ceiling(t_parse *data, char *str)
{
    char **split;
    int len;
    if(data->ceiling_color)
        return (DOUBLICATE);
    split = ft_split(str, ' ');
    if(!split)
        return(MALLOC);
    len = count_array_len(split);
    if(len != 2)
    {
        free_array(split);
        return(len > 2 ? TOO_MANY_VALUES : TOO_FEW_VALUES);
    }
    if(ft_strcmp("C", split[0]))
    {
        free_array(split);
        return (INVALID_KEY);
    }
    data->ceiling_color = get_color(split[1]);
    free_array(split);
    if(data->ceiling_color < 0)
        return (data->ceiling_color);
    return (SUCCESS);
}
