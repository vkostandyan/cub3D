/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:04:30 by kgalstya          #+#    #+#             */
/*   Updated: 2025/01/11 21:41:30 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
}
