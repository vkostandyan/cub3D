/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:51:41 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/14 17:53:32 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_color2(char **split, int len)
{
	int	red;
	int	green;
	int	blue;

	if (count_array_len(split) != 3)
	{
		free_array(split);
		if (len > 3)
			return (TOO_MANY_VALUES);
		return (TOO_FEW_VALUES);
	}
	if (!check_digit(split))
		return (free_array(split), INVALID_COLOR_ARGUMENTS);
	if (ft_strlen(split[0]) > 10 || ft_strlen(split[1]) > 10
		|| ft_strlen(split[2]) > 10)
		return (free_array(split), INVALID_RANGE);
	red = ft_atoi(split[0]);
	green = ft_atoi(split[1]);
	blue = ft_atoi(split[2]);
	free_array(split);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
		return (INVALID_RANGE);
	return (red * 256 * 256 + green * 256 + blue);
}

int	get_color(char *str)
{
	char	**split;
	char	*tmp;
	int		len;

	if ((str[0] && str[0] == ',') || (str[ft_strlen(str) - 1]
			&& str[ft_strlen(str) - 1] == ','))
		return (EDGE_COMMA);
	if (ft_strstr(str, ",,"))
		return (DOUBLE_COMMA);
	if (ft_strstr(str, "\n"))
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		split = ft_split(tmp, ',');
	}
	else
		split = ft_split(str, ',');
	if (!split)
		return (MALLOC);
	len = count_array_len(split);
	return (get_color2(split, len));
}

int	set_floor(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->floor_color)
		return (DOUBLICATE);
	split = ft_split(str, ' ');
	if (!split)
		return (MALLOC);
	len = count_array_len(split);
	if (len != 2)
	{
		free_array(split);
		if (len > 2)
			return (TOO_MANY_VALUES);
		return (TOO_FEW_VALUES);
	}
	if (ft_strcmp("F", split[0]))
		return (free_array(split), INVALID_KEY);
	data->floor_color = get_color(split[1]);
	free_array(split);
	if (data->floor_color < 0)
		return (data->floor_color);
	return (SUCCESS);
}

int	set_ceiling(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->ceiling_color)
		return (DOUBLICATE);
	split = ft_split(str, ' ');
	if (!split)
		return (MALLOC);
	len = count_array_len(split);
	if (len != 2)
	{
		free_array(split);
		if (len > 2)
			return (TOO_MANY_VALUES);
		return (TOO_FEW_VALUES);
	}
	if (ft_strcmp("C", split[0]))
		return (free_array(split), INVALID_KEY);
	data->ceiling_color = get_color(split[1]);
	free_array(split);
	if (data->ceiling_color < 0)
		return (data->ceiling_color);
	return (SUCCESS);
}
