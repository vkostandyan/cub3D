/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:36:34 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:37:44 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "parsing.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCREENWIDTH 1900
# define SCREENHEIGHT 1000
# define TILE_SIZE 64
# define STEP_SIZE 4
# define FOV 60
# define PLAYER_SPEED 3
# define ROTATION_SPEED 0.045
# define MOUSE_ROT_SPEED 0.2
# define IMG_SIZE 64

# define OFF_ESC 53
# define OFF_X 17

# define UP_ARR 65362
# define DOWN_ARR 65364
# define LEFT_ARR 123
# define RIGHT_ARR 124

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

# define KEY_PRESS 2
# define KEY_PRESS_MASK 0
# define KEY_PRESS_Z 6
# define KEY_PRESS_X 7
# define KEY_PRESS_Y 16

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define RESET "\033[0m"

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			color;
	int			w;
	int			h;
}				t_img;

typedef struct s_player
{
	int			ply_x;
	int			ply_y;
	float		ply_angle;
	float		fov_rd;
	int			move_flag;
}				t_player;

typedef struct s_map
{
	char		**map2d;
	int			ply_x_start;
	int			ply_y_start;
	int			width_map_x;
	int			height_map_y;

}				t_map;

typedef struct s_ray
{
	float		ray_angle;
	float		distance;
	int			flag;
	float		horiz_x;
	float		horiz_y;
	float		vert_x;
	float		vert_y;
}				t_ray;

typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
}				t_texture;

typedef struct s_cub3D
{
	void		*mlx;
	void		*mlx_win;
	int			wall_h;

	t_texture	*tex;
	t_parse		*parse_data;
	t_map		map;
	t_player	player;
	t_img		img_stract;
	t_ray		ray;
}				t_cub3D;

typedef struct s_move
{
	int			mx;
	int			my;
}				t_move;

//  game  //
void			game(char *argv, t_parse *pars_data);
void			free_and_exit(t_cub3D *data);
void			destroy_img_tex(t_cub3D *data);
int				close_window(t_cub3D *data);

//  casting rays  //
void			cast_rays(t_cub3D *data);
float			check_angle(float angle);
void			instal_the_wall(t_cub3D *data, int ray);

//  movement  //
int				mlx_for_move(int keycode, t_cub3D *data);
void			movment(t_cub3D *data);
void			rotate_player(t_cub3D *data, int flag, float speed);
int				mouse_move(int x, int y, t_cub3D *data);

//  for drawing  //
void			mlx_pixel_put_with_checking(t_cub3D *data, int x, int y,
					int color);
void			mlx_pixel_put_img(t_cub3D *data, int x, int y, int color);
t_img			*get_texture(t_cub3D *data);
unsigned int	get_color_for_draw(int x, int y, t_img *text_img);

//  textures  //
void			set_textures(t_cub3D *data);

#endif
