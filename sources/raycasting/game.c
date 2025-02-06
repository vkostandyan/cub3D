/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:11:57 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:55 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

	// printf(RED "🌎ERROR MESSEGE\n" RESET),exit(1);
void	my_mlx_image_clear(t_img *img)
{
	int	offset;

	offset = 0;
	while (offset < (screenHeight * img->line_length))
	{
		*(img->addr + offset) = 0x0;
		offset++;
	}
}

int game_loop(t_cub3D *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	data->img_stract.img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->img_stract.addr = mlx_get_data_addr(data->img_stract.img, &data->img_stract.bits_per_pixel, &data->img_stract.line_length, &data->img_stract.endian);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_stract.img, 0, 0);
	my_mlx_image_clear(&data->img_stract);
	return(0);
}

int	win_hooks(int keycode, t_cub3D *data)
{
	if (keycode == OFF_ESC)
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_destroy_window(data->mlx, data->mlx_win);
		// system("leaks cub3D");
		exit(0);
	}
	return (0);
}

int	close_window(t_cub3D *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_destroy_window(data->mlx, data->mlx_win);
	// system("leaks cub3D");
	exit(0);
	return (0);
}

void	print_array_a(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf(CYAN "%s\n" RESET, str[i]);
		i++;
	}
}

void init_parse_data(t_cub3D *data)
{
	data->map.ply_y_start = data->parse_data->player.y - 1;
	data->map.ply_x_start = data->parse_data->player.x - 1;
	data->map.height_map_y = data->parse_data->map_height;
	data->map.width_map_x = data->parse_data->map_width;
	data->map.map2d = data->parse_data->map;
	print_array_a(data->map.map2d);
	printf(YELLOW "data->map.width_map_x -> " MAGENTA "%d\n" RESET, data->map.width_map_x);
	printf(YELLOW "data->map.height_map_y -> " MAGENTA "%d\n" RESET, data->map.height_map_y);
	printf(YELLOW "ply_x_start -> " MAGENTA "%d\n" RESET, data->map.ply_x_start);
	printf(YELLOW "ply_y_start -> " MAGENTA "%d\n" RESET, data->map.ply_y_start);
}
void init_player_data(t_cub3D *data)
{
	data->player.ply_x = data->map.ply_x_start * TILE_SIZE + TILE_SIZE / 2;
	data->player.ply_y = data->map.ply_y_start * TILE_SIZE + TILE_SIZE / 2;
	if(data->parse_data->player.start_direction == NORTH)
		data->player.ply_angle =  3 * M_PI / 2;
	else if(data->parse_data->player.start_direction == SOUTH)
		data->player.ply_angle = M_PI / 2;
	else if(data->parse_data->player.start_direction == EAST)
		data->player.ply_angle = 0;
	else if(data->parse_data->player.start_direction == WEST)
		data->player.ply_angle = M_PI;
	data->player.move_flag = 0;
	data->player.fov_rd = (FOV * M_PI) / 180;
}

int mouse_move(int x, int y, t_cub3D *data)
{
	static int prev_x;
	(void)y;
	(void)data;
	if(prev_x > x)
		rotate_player(data, 0, MOUSE_ROT_SPEED);
	else if(prev_x < x)
		rotate_player(data, 1, MOUSE_ROT_SPEED);
	prev_x = x;
	return(0);
}

// void init_texture_data(t_cub3D *data)
// {
// 	data->tex.ea.img =
// }

int get_textures_adrr(t_cub3D *data)
{
	data->tex->ea.addr = mlx_get_data_addr(data->tex->ea.img, &data->tex->ea.bits_per_pixel, &data->tex->ea.line_length, &data->tex->ea.endian);
	// printf(GREEN"%s\n"RESET, mlx_get_data_addr(data->tex.ea.img, &data->tex.ea.bits_per_pixel, &data->tex.ea.line_length, &data->tex.ea.endian));
	data->tex->we.addr = mlx_get_data_addr(data->tex->we.img, &data->tex->we.bits_per_pixel, &data->tex->we.line_length, &data->tex->we.endian);
	data->tex->no.addr = mlx_get_data_addr(data->tex->no.img, &data->tex->no.bits_per_pixel, &data->tex->no.line_length, &data->tex->no.endian);
	data->tex->so.addr = mlx_get_data_addr(data->tex->so.img, &data->tex->so.bits_per_pixel, &data->tex->so.line_length, &data->tex->so.endian);
	return(0);
}

void set_textures(t_cub3D *data)
{
	data->tex = malloc(sizeof(t_texture));
	if(!data->tex)
		printf(RED"MALLLLLOOOC\n"RESET), exit(1);
	data->tex->ea.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->east, &data->tex->ea.w, &data->tex->ea.h);
	data->tex->we.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->west, &data->tex->we.w, &data->tex->we.h);
	data->tex->no.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->north, &data->tex->no.w, &data->tex->no.h);
	data->tex->so.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->south, &data->tex->so.w, &data->tex->so.h);
	// if(data->tex->ea.w != 64 || data->tex->no.w != 64 || data->tex->so.w != 64 || data->tex->we.w != 64 )
	// // 	printf(YELLOW"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"RESET), exit(1);
	// if(data->tex->ea.h != 64 || data->tex->no.h != 64 || data->tex->so.h != 64 || data->tex->we.h != 64 )
	// 	printf(YELLOW"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"RESET), exit(1);
	if(!data->tex->ea.img || !data->tex->we.img || !data->tex->no.img || !data->tex->so.img)
		printf(YELLOW"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"RESET), exit(1);
	get_textures_adrr(data);
}

void game(char *argv, t_parse *parse_inp)
{
	t_cub3D data;
	(void)argv;

	data.parse_data = parse_inp;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, screenWidth, screenHeight, "cub3D");
	init_parse_data(&data);
	init_player_data(&data);
	set_textures(&data);
	// init_texture_data(&data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.mlx_win, KEY_PRESS, KEY_PRESS_MASK, mlx_for_move,
		&data);
	mlx_hook(data.mlx_win, 6, 0, mouse_move, &data);
	mlx_hook(data.mlx_win, OFF_X, KEY_PRESS_MASK, close_window,
		&data);
	mlx_loop(data.mlx);

}
