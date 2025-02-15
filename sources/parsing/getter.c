/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:03:17 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/15 16:21:22 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_type	get_player_start_direction(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'E')
		return (EAST);
	if (c == 'W')
		return (WEST);
	return (NOT_VALID);
}

void	get_player_position(t_parse *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player.x = j + 1;
				data->player.y = i + 1;
				data->player.start_direction = \
					get_player_start_direction(data->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	get_map_height_and_width(t_parse *data)
{
	int	i;
	int	max_len;
	int	cur_len;

	i = 0;
	max_len = 0;
	cur_len = 0;
	while (data->map[i])
	{
		cur_len = ft_strlen(data->map[i]);
		if (cur_len > max_len)
			max_len = cur_len;
		i++;
	}
	data->map_width = max_len;
	data->map_height = i;
}

void	get_textures_fds(t_parse *data)
{
	data->north_fd = open(data->north, O_RDONLY);
	if (data->north_fd == -1)
		send_file_open_error(data->north);
	data->south_fd = open(data->south, O_RDONLY);
	if (data->south_fd == -1)
	{
		close(data->north_fd);
		send_file_open_error(data->south);
	}
	data->east_fd = open(data->east, O_RDONLY);
	if (data->east_fd == -1)
	{
		close(data->north_fd);
		close(data->south_fd);
		send_file_open_error(data->east);
	}
	data->west_fd = open(data->west, O_RDONLY);
	if (data->west_fd == -1)
	{
		close(data->north_fd);
		close(data->south_fd);
		close(data->east_fd);
		send_file_open_error(data->west);
	}
}

// void get_player_position(t_parse *data)
// {
//     int i;
//     int j;

//     i = 0;
//     while(data->map[i])
//     {
//         j = 0;
//         while(data->map[i][j])
//         {
//             if(data->map[i][j] == 'N')
//             {
//                 data->player.x = j + 1;
//                 data->player.y = i + 1;
//                 data->player.start_direction = NORTH;
//             }
//             if(data->map[i][j] == 'S')
//             {
//                 data->player.x = j + 1;
//                 data->player.y = i + 1;
//                 data->player.start_direction = SOUTH;
//             }
//             if(data->map[i][j] == 'E')
//             {
//                 data->player.x = j + 1;
//                 data->player.y = i + 1;
//                 data->player.start_direction = EAST;
//             }
//             if(data->map[i][j] == 'W')
//             {
//                 data->player.x = j + 1;
//                 data->player.y = i + 1;
//                 data->player.start_direction = WEST;
//             }
//             j++;
//         }
//         i++;
//     }
// }
