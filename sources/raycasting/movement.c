/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:53:36 by kgalstya          #+#    #+#             */
/*   Updated: 2025/01/22 16:06:11 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void move_player(t_cub3D *data, t_move *move_cords)
{
	int x_map_cords;
	int y_map_cords;
	int new_x;
	int new_y;

	printf(BLUE"MX new_x ->> %d \n", move_cords->mx);
	printf(BLUE"MY new_y ->> %d \n", move_cords->my);
	new_x = roundf(move_cords->mx * TILE_SIZE + data->player.ply_x);
	new_y = roundf(move_cords->my * TILE_SIZE + data->player.ply_y);
	x_map_cords = new_x / TILE_SIZE;
	y_map_cords = new_y / TILE_SIZE;
	printf(BLUE"new_x ->> %d \n", new_x);
	printf(BLUE"new_y ->> %d \n", new_y);
	printf(RED"x_map_cords ->> %d \n", x_map_cords);
	printf(RED"y_map_cords ->> %d \n"RESET, y_map_cords);
	if(y_map_cords < data->map.width_map_x && y_map_cords >= 0 && x_map_cords >= 0 && x_map_cords < data->map.height_map_y)
	{
		if(data->map.map2d[y_map_cords][x_map_cords] != '1' && data->map.map2d[y_map_cords][data->player.ply_x / TILE_SIZE] != '1'
				&& data->map.map2d[data->player.ply_y / TILE_SIZE][x_map_cords] != '1')
		{
			data->player.ply_x = new_x;
			data->player.ply_y = new_y;
		}
	}
}

void movment(t_cub3D *data)
{
	t_move move_cords;

	printf(YELLOW"%d\n"RESET, data->player.move_flag);

	if(data->player.move_flag == 1) // KEY_W
	{
		move_cords.mx = cos(data->player.ply_angle) * PLAYER_SPEED;
		move_cords.my = sin(data->player.ply_angle) * PLAYER_SPEED;
		data->player.move_flag = 0;
		move_player(data, &move_cords);
	}
	else if(data->player.move_flag == 2) // KEY_D
	{
		move_cords.mx = -sin(data->player.ply_angle) * PLAYER_SPEED;
		move_cords.my = cos(data->player.ply_angle) * PLAYER_SPEED;
		data->player.move_flag = 0;
		move_player(data, &move_cords);
	}
	else if(data->player.move_flag == 3) // KEY_S
	{
		move_cords.mx = -cos(data->player.ply_angle) * PLAYER_SPEED;
		move_cords.my = -sin(data->player.ply_angle) * PLAYER_SPEED;
		data->player.move_flag = 0;
		move_player(data, &move_cords);
	}
	else if(data->player.move_flag == 4) // KEY_A
	{
		move_cords.mx = sin(data->player.ply_angle) * PLAYER_SPEED;
		move_cords.my = -cos(data->player.ply_angle) * PLAYER_SPEED;
		data->player.move_flag = 0;
		move_player(data, &move_cords);
	}
	// move_player(data, &move_cords);
}

void	rotate_player(t_cub3D *data, int flag, float speed)
{
	if (flag == 1)
	{
		data->player.ply_angle += speed;
		if (data->player.ply_angle > 2 * M_PI)
			data->player.ply_angle -= 2 * M_PI;
	}
	else
	{
		data->player.ply_angle -= speed;
		if (data->player.ply_angle < 0)
			data->player.ply_angle += 2 * M_PI;
	}
}

// void see_up_and_down()
// {

// }

int mlx_for_move(int keycode, t_cub3D *data)
{
	if(keycode == OFF_ESC)
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_destroy_window(data->mlx, data->mlx_win);
		// system("leaks cub3D");
		exit(0);
	}
	if(keycode == LEFT_ARR)
	{
		rotate_player(data, 0, ROTATION_SPEED);
		movment(data);
		return(0);
	}
	else if(keycode == RIGHT_ARR)
	{
		rotate_player(data, 1, ROTATION_SPEED);
		movment(data);
		return(0);
	}
	// if(keycode == UP_ARR)
	// {

	// }
	if(keycode == KEY_W)
	{
		data->player.move_flag = 1;
		movment(data);
	}
	else if(keycode == KEY_D)
	{
		data->player.move_flag = 2;
		movment(data);
	}
	else if(keycode == KEY_S)
	{
		data->player.move_flag = 3;
		movment(data);
	}
	else if(keycode == KEY_A)
	{
		data->player.move_flag = 4;
		movment(data);
	}
	return(0);
}
