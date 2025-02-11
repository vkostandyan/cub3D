/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:30:10 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/11 13:33:09 by kgalstya         ###   ########.fr       */
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
