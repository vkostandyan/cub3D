/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:47:00 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/18 18:13:24 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void destroy_img_tex(t_cub3D *data)
{
	if(data->tex->no.img)
		mlx_destroy_image(data->mlx, data->tex->no.img);
	if(data->tex->ea.img)
		mlx_destroy_image(data->mlx, data->tex->ea.img);
	if(data->tex->we.img)
		mlx_destroy_image(data->mlx, data->tex->we.img);
	if(data->tex->so.img)
		mlx_destroy_image(data->mlx, data->tex->so.img);
	free(data->tex);
	data->tex = NULL;
}

void free_and_exit(t_cub3D *data)
{
	destroy_img_tex(data);
	if(data->img_stract.img)
		mlx_destroy_image(data->mlx, data->img_stract.img);
	if(data->mlx_win)
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		mlx_destroy_window(data->mlx, data->mlx_win);
	}
	// system("leaks cub3D");
	exit(1);
}
