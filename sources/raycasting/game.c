/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:11:57 by kgalstya          #+#    #+#             */
/*   Updated: 2025/01/11 17:47:17 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

	// printf(RED "🌎ERROR MESSEGE\n" RESET),exit(1);

int game_loop(t_cub3D *dt)
{
	t_cub3D *data;

	data = dt;
	data->img_stract.img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	// hook(data->mlx, 0, 0);  FOR MOVING
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_stract.img, 0, 0);
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

void	print_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf(CYAN "%s\n" RESET, str[i]);
		i++;
	}
}

void init_map(t_map *map)
{
	map->height_map_y = 10;
	map->width_map_x = 5;
	map->ply_x_start = 3;
	map->ply_y_start = 5;
	map->map2d = (char **)malloc(sizeof(char *) * (map->height_map_y + 1));
	map->map2d[0] = ft_strdup("11111");
	map->map2d[1] = ft_strdup("10001");
	map->map2d[2] = ft_strdup("10001");
	map->map2d[3] = ft_strdup("10001");
	map->map2d[4] = ft_strdup("10P01");
	map->map2d[5] = ft_strdup("10001");
	map->map2d[6] = ft_strdup("10001");
	map->map2d[7] = ft_strdup("10001");
	map->map2d[8] = ft_strdup("10001");
	map->map2d[9] = ft_strdup("11111");
	map->map2d[10] = NULL;

	print_array(map->map2d);
	printf(YELLOW "ply_x_start -> " MAGENTA "%d\n" RESET, map->ply_x_start);
	printf(YELLOW "ply_y_start -> " MAGENTA "%d\n" RESET, map->ply_y_start);
}
void init_player_data(t_cub3D *data)
{
	data->player.ply_x = data->map.ply_x_start * TILE_SIZE + TILE_SIZE / 2;
	data->player.ply_y = data->map.ply_y_start * TILE_SIZE + TILE_SIZE / 2;
	data->player.ply_angle = M_PI;
	data->player.fov_rd = (FOV * M_PI) / 180;
}

void game(char *argv)
{
	t_cub3D data;
	(void)argv;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, screenWidth, screenHeight, "cub3D");
	init_map(&data.map);
	init_player_data(&data);
	printf("a\n");
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.mlx_win, KEY_PRESS, KEY_PRESS_MASK, win_hooks,
		&data);
	mlx_hook(data.mlx_win, OFF_X, KEY_PRESS_MASK, close_window,
		&data);
	mlx_loop(data.mlx);

}
