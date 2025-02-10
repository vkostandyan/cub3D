/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:04:30 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/10 14:34:00 by kgalstya         ###   ########.fr       */
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
	mlx_pixel_put_img(data, x, y, color);
}

t_img *get_texture(t_cub3D *data)
{
	data->ray.ray_angle = check_angle(data->ray.ray_angle);
	if(data->ray.flag == 0)
	{
		if(data->ray.ray_angle >= M_PI / 2 && data->ray.ray_angle <= 3 * (M_PI / 2))
			return(&data->tex->we);
		else
			return(&data->tex->ea);
	}
	else
	{
		if(data->ray.ray_angle >= 0 && data->ray.ray_angle <= M_PI)
			return(&data->tex->so);
		else
			return(&data->tex->no);
	}
	return(&data->tex->no);
}

unsigned int get_color_for_draw(int x, int y, t_img *text_img)
{
	unsigned int color;
	char *dst;

	if(x >= 0 && x < text_img->w && y >= 0 && y < text_img->h)
	{
		dst = text_img->addr + (y * text_img->line_length + x * (text_img->bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		return(color);
	}
	return(0);
}

double get_dx(t_cub3D *data, t_img *text_img)
{
	double dx;
	if(data->ray.flag == 1)
		dx = (int)fmodf((data->ray.horiz_x * (text_img->w / TILE_SIZE)), text_img->w);
	else
		dx = (int)fmodf((data->ray.vert_y * (text_img->w / TILE_SIZE)), text_img->w);
	return(dx);
}

void draw_wall(t_cub3D *data, int ray, double tieri_pix, double tveri_pix)
{
	unsigned int color;
	double		dx;
	double		dy;
	double		factor;
	t_img		*text_img;

	text_img = get_texture(data);
	factor = (double)text_img->h / data->wall_h;
	dx = get_dx(data, text_img);
	dy = (tieri_pix - (screenHeight / 2) + (data->wall_h / 2)) * factor;
	if(dy < 0)
		dy = 0;
	while(tieri_pix < tveri_pix)
	{
		color = get_color_for_draw(dx , dy , text_img);
		dy += factor;
		mlx_pixel_put_with_checking(data, ray, tieri_pix++, color);
	}
}

void draw_floor_and_ceiling(t_cub3D *data, int ray, double tieri_pix, double tveri_pix)
{
	int tmp;

	tmp = tveri_pix;
	while(tmp < screenHeight)
		mlx_pixel_put_with_checking(data, ray, tmp++, data->parse_data->floor_color);
	tmp = 0;
	while(tmp < tieri_pix)
		mlx_pixel_put_with_checking(data, ray, tmp++, data->parse_data->ceiling_color);
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
	data->wall_h = wall_h;
	draw_wall(data, ray, tieri_pix, tveri_pix);
	draw_floor_and_ceiling(data, ray, tieri_pix, tveri_pix);
}
