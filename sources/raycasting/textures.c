/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:26:45 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/19 17:40:32 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_textures_adrr(t_cub3D *data)
{
	data->tex->ea.addr = mlx_get_data_addr(data->tex->ea.img,
			&data->tex->ea.bits_per_pixel, &data->tex->ea.line_length,
			&data->tex->ea.endian);
	data->tex->we.addr = mlx_get_data_addr(data->tex->we.img,
			&data->tex->we.bits_per_pixel, &data->tex->we.line_length,
			&data->tex->we.endian);
	data->tex->no.addr = mlx_get_data_addr(data->tex->no.img,
			&data->tex->no.bits_per_pixel, &data->tex->no.line_length,
			&data->tex->no.endian);
	data->tex->so.addr = mlx_get_data_addr(data->tex->so.img,
			&data->tex->so.bits_per_pixel, &data->tex->so.line_length,
			&data->tex->so.endian);
	if (!data->tex->so.addr || !data->tex->no.addr || !data->tex->we.addr
		|| !data->tex->ea.addr)
	{
		destroy_img_tex(data);
		printf(RED "HAVE PROBLEM WITH IMAGE\n" RESET);
		exit(1);
	}
	return (0);
}

void	set_textures(t_cub3D *data)
{
	data->tex = malloc(sizeof(t_texture));
	if (!data->tex)
		free_and_exit(data);
	data->tex->ea.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->east,
			&data->tex->ea.w, &data->tex->ea.h);
	data->tex->we.img = mlx_xpm_file_to_image(data->mlx, data->parse_data->west,
			&data->tex->we.w, &data->tex->we.h);
	data->tex->no.img = mlx_xpm_file_to_image(data->mlx,
			data->parse_data->north, &data->tex->no.w, &data->tex->no.h);
	data->tex->so.img = mlx_xpm_file_to_image(data->mlx,
			data->parse_data->south, &data->tex->so.w, &data->tex->so.h);
	if (!data->tex->ea.img || !data->tex->we.img || !data->tex->no.img
		|| !data->tex->so.img)
	{
		printf(RED "CAN'T USE IMAGE\n" RESET);
		destroy_img_tex(data);
		exit(1);
	}
	get_textures_adrr(data);
}
