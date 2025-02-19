/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:11:57 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/19 17:41:36 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

void	my_mlx_image_clear(t_img *img)
{
	int	offset;

	offset = 0;
	while (offset < (SCREENHEIGHT * img->line_length))
	{
		*(img->addr + offset) = 0x0;
		offset++;
	}
}

int	game_loop(t_cub3D *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	data->img_stract.img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	data->img_stract.addr = mlx_get_data_addr(data->img_stract.img,
			&data->img_stract.bits_per_pixel, &data->img_stract.line_length,
			&data->img_stract.endian);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_stract.img, 0,
		0);
	my_mlx_image_clear(&data->img_stract);
	return (0);
}

void	init_parse_data(t_cub3D *data)
{
	data->map.ply_y_start = data->parse_data->player.y - 1;
	data->map.ply_x_start = data->parse_data->player.x - 1;
	data->map.height_map_y = data->parse_data->map_height;
	data->map.width_map_x = data->parse_data->map_width;
	data->map.map2d = data->parse_data->map;
}

void	init_player_data(t_cub3D *data)
{
	data->player.ply_x = data->map.ply_x_start * TILE_SIZE + TILE_SIZE / 2;
	data->player.ply_y = data->map.ply_y_start * TILE_SIZE + TILE_SIZE / 2;
	if (data->parse_data->player.start_direction == NORTH)
		data->player.ply_angle = 3 * M_PI / 2;
	else if (data->parse_data->player.start_direction == SOUTH)
		data->player.ply_angle = M_PI / 2;
	else if (data->parse_data->player.start_direction == EAST)
		data->player.ply_angle = 0;
	else if (data->parse_data->player.start_direction == WEST)
		data->player.ply_angle = M_PI;
	data->player.move_flag = 0;
	data->player.fov_rd = (FOV * M_PI) / 180;
}

void	game(char *argv, t_parse *parse_inp)
{
	t_cub3D	data;

	(void)argv;
	data.parse_data = parse_inp;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	init_parse_data(&data);
	init_player_data(&data);
	set_textures(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.mlx_win, KEY_PRESS, KEY_PRESS_MASK, mlx_for_move, &data);
	mlx_hook(data.mlx_win, 6, 0, mouse_move, &data);
	mlx_hook(data.mlx_win, OFF_X, KEY_PRESS_MASK, close_window, &data);
	mlx_loop(data.mlx);
}
