/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:45:45 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/11 13:46:47 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float check_angle(float angle)
{
	if(angle < 0)
		angle += 2 * M_PI;
	if(angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return(angle);
}

int check_circle(float angle, int flag)
{
	if (flag == 1)
	{
		if (angle > 0 && angle < M_PI)
		return (1);
	}
	else if (flag == 0)
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		return (1);
	}
	return (0);
}

int inter_check(float angle, float *inter_value, float *step, int is_horiz)
{
	if(is_horiz)
	{
		if(angle > 0 && angle < M_PI)
		{
			*inter_value += TILE_SIZE;
			return(0);
		}
		*step *= -1;
	}
	else
	{
		if(!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2))
		{
			*inter_value += TILE_SIZE;
			return(0);
		}
		*step *= -1;
	}
	return(1);
}

int wall_hit(float x, float y, t_cub3D *data)
{
	int x_map;
	int y_map;

	if(x < 0 || y < 0)
		return(0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if(x_map > data->map.width_map_x || y_map > data->map.height_map_y)
		return(0);
	if(data->map.map2d[y_map] && x_map <= (int)ft_strlen(data->map.map2d[y_map]))
	{
		if(data->map.map2d[y_map][x_map] == '1')
			return(0);
	}
	return(1);
}

float get_v_inter(t_cub3D *data, float angle)
{
	float step_x;
	float step_y;
	float v_x;
	float v_y;
	int pixel;

	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(angle);
	v_x = floor(data->player.ply_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &step_x, 0);
	v_y = data->player.ply_y + (v_x - data->player.ply_x) * tan(angle);
	if((check_circle(angle, 1) && step_y < 0) || (!check_circle(angle, 1) && step_y > 0))
		step_y *= -1;
	while(wall_hit(v_x - pixel, v_y, data))
	{
		v_x += step_x;
		v_y += step_y;
	}
	data->ray.vert_x = v_x;
	data->ray.vert_y = v_y;
	return(sqrt(pow(v_x - data->player.ply_x,2) + pow(v_y - data->player.ply_y,2)));
}

float get_h_inter(t_cub3D *data, float angle)
{
	float step_x;
	float step_y;
	float h_x;
	float h_y;
	int pixel;

	step_y = TILE_SIZE;
	step_x = TILE_SIZE / tan(angle);
	h_y = floor(data->player.ply_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &step_y, 1);
	h_x = data->player.ply_x + (h_y - data->player.ply_y) / tan(angle);
	if((check_circle(angle, 0) && step_x > 0) || (!check_circle(angle, 0) && step_x < 0))
		step_x *= -1;
	while(wall_hit(h_x, h_y - pixel, data))
	{
		h_x += step_x;
		h_y += step_y;
	}
	data->ray.horiz_x = h_x;
	data->ray.horiz_y = h_y;
	return(sqrt(pow(h_x - data->player.ply_x,2) + pow(h_y - data->player.ply_y,2)));
}

void cast_rays(t_cub3D *data)
{
	double h_inter;
	double v_inter;
	int ray;

	ray = 0;
	data->ray.ray_angle = data->player.ply_angle - (data->player.fov_rd / 2);
	while(ray < screenWidth)
	{
		data->ray.flag = 0;
		h_inter = get_h_inter(data, check_angle(data->ray.ray_angle));
		v_inter = get_v_inter(data, check_angle(data->ray.ray_angle));
		if(v_inter <= h_inter)
			data->ray.distance = v_inter;
		else
		{
			data->ray.distance = h_inter;
			data->ray.flag = 1;
		}
		instal_the_wall(data, ray);
		ray++;
		data->ray.ray_angle += (data->player.fov_rd / screenWidth);
	}
}
