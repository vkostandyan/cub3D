/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:35:47 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/19 17:43:25 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_cub3D *data)
{
	static int	prev_x;

	(void)y;
	(void)data;
	if (prev_x > x)
		rotate_player(data, 0, MOUSE_ROT_SPEED);
	else if (prev_x < x)
		rotate_player(data, 1, MOUSE_ROT_SPEED);
	prev_x = x;
	return (0);
}

int	close_window(t_cub3D *data)
{
	free_and_exit(data);
	return (0);
}

float	check_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	check_circle(float angle, int flag)
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
