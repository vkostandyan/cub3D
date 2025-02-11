/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:35:47 by kgalstya          #+#    #+#             */
/*   Updated: 2025/02/11 13:38:20 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int mouse_move(int x, int y, t_cub3D *data)
{
	static int prev_x;
	(void)y;
	(void)data;
	if(prev_x > x)
		rotate_player(data, 0, MOUSE_ROT_SPEED);
	else if(prev_x < x)
		rotate_player(data, 1, MOUSE_ROT_SPEED);
	prev_x = x;
	return(0);
}

int	close_window(t_cub3D *data)
{
	free_and_exit(data);
	return(0);
}
