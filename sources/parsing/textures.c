/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:58:25 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/15 15:58:55 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_north(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->north)
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
	if (ft_strcmp("NO", split[0]))
		return (free_array(split), INVALID_KEY);
	data->north = ft_strdup(split[1]);
	free_array(split);
	if (!data->north)
		return (MALLOC);
	return (SUCCESS);
}

int	set_south(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->south)
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
	if (ft_strcmp("SO", split[0]))
		return (free_array(split), INVALID_KEY);
	data->south = ft_strdup(split[1]);
	free_array(split);
	if (!data->south)
		return (MALLOC);
	return (SUCCESS);
}

int	set_east(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->east)
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
	if (ft_strcmp("EA", split[0]) != 0)
		return (free_array(split), INVALID_KEY);
	data->east = ft_strdup(split[1]);
	free_array(split);
	if (!data->east)
		return (MALLOC);
	return (SUCCESS);
}

int	set_west(t_parse *data, char *str)
{
	char	**split;
	int		len;

	if (data->west)
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
	if (ft_strcmp("WE", split[0]))
		return (free_array(split), INVALID_KEY);
	data->west = ft_strdup(split[1]);
	free_array(split);
	if (!data->west)
		return (MALLOC);
	return (SUCCESS);
}

int	save_textures(t_parse *data, char *str, int type)
{
	if (type == NORTH)
		return (set_north(data, str));
	if (type == SOUTH)
		return (set_south(data, str));
	if (type == EAST)
		return (set_east(data, str));
	if (type == WEST)
		return (set_west(data, str));
	if (type == FLOOR)
		return (set_floor(data, str));
	if (type == CEILING)
		return (set_ceiling(data, str));
	return (SUCCESS);
}
