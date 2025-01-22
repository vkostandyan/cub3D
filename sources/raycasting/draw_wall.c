/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:04:30 by kgalstya          #+#    #+#             */
/*   Updated: 2025/01/21 19:24:32 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_pixel_put_img(t_cub3D *data, int x, int y, int color)
{
	char	*dst;

	if (x >= screenWidth || y >= screenHeight)
		return ;
	dst = data->img_stract.addr + (y * data->img_stract.line_length + x * (data->img_stract.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void mlx_pixel_put_with_checking(t_cub3D *data, int x, int y, int color)
{
	if(x < 0)
		return ;
	if(x >= screenWidth)
		return ;
	if(y < 0)
		return ;
	if(y >= screenHeight)
		return ;
	mlx_pixel_put_img(data, x, y, color); // put the pixel
}

int get_color_for_draw(t_cub3D *data)
{
	data->ray.ray_angle = check_angle(data->ray.ray_angle);
	if(data->ray.flag == 0)
	{
		if(data->ray.ray_angle >= M_PI / 2 && data->ray.ray_angle <= 3 * (M_PI / 2))
			return(8421504); // W gray
		else
			return(16776960); // E yelow
	}
	else
	{
		if(data->ray.ray_angle >= 0 && data->ray.ray_angle <= M_PI)
			return(65280); // S green
		else
			return(16711680); // N  red
	}
	return(256);
}

void draw_wall(t_cub3D *data, int ray, double tieri_pix, double tveri_pix)
{
	int color;
	color = get_color_for_draw(data);
	while(tieri_pix < tveri_pix)
	{

		mlx_pixel_put_with_checking(data, ray, tieri_pix++, color);
		tieri_pix++;
	}
}

void draw_floor_and_ceiling(t_cub3D *data, int ray, double tieri_pix, double tveri_pix)
{
	int tmp;

	tmp = tveri_pix;
	while(tmp < screenHeight)
		mlx_pixel_put_with_checking(data, ray, tmp++, 8454016);
	tmp = 0;
	while(tmp < tieri_pix)
		mlx_pixel_put_with_checking(data, ray, tmp++, 8900331);
}

void instal_the_wall(t_cub3D *data, int ray)
{
	double wall_h;
	double tieri_pix;
	double tveri_pix;

	data->ray.distance *= cos(check_angle(data->ray.ray_angle - data->player.ply_angle));
	wall_h = (TILE_SIZE / data->ray.distance) * ((screenWidth / 2) * tan(data->player.fov_rd / 2));
	tieri_pix = (screenHeight / 2) - (wall_h / 2);
	tveri_pix = (screenHeight / 2) + (wall_h / 2);
	if(tveri_pix > screenHeight)
		tveri_pix = screenHeight;
	if(tieri_pix < 0)
		tieri_pix = 0;
	draw_wall(data, ray, tieri_pix, tveri_pix);
	draw_floor_and_ceiling(data, ray, tieri_pix, tveri_pix);
}
