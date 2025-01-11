#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "mlx.h"
#include <math.h>
#include "libft.h"

# define screenWidth 1900
# define screenHeight 1000
# define TILE_SIZE 30
# define FOV 60
// # define ROTATION_SPEED 0.045
// # define PLAYER_SPEED 4


# define OFF_ESC 53
# define OFF_X 17

# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define KEY_PRESS_Z 6
# define KEY_PRESS_X 7
# define KEY_PRESS_Y 16

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define RESET   "\033[0m"


// typedef struct s_parse
// {
//     char		**map;
//     char		*north;
// 	char		*west;
// 	char		*east;
// 	char		*south;
//     int			ceiling_color;
// 	int			floor_color;


// }               t_parse;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			color;
}				t_img;

typedef struct s_player
{
	int ply_x;
	int ply_y;
	float ply_angle;
	float fov_rd; // field of view
}				t_player;

typedef struct s_map
{
	char **map2d;
	int  ply_x_start;
	int  ply_y_start;
	int  width_map_x;
	int  height_map_y;

}				t_map;

typedef struct s_ray
{
	float ray_angle;
	float distance;
	int flag;
}				t_ray;


typedef struct s_cub3D
{
	void *mlx;
	void *mlx_win;

	t_map map;
	t_player player;
	t_img img_stract;
	t_ray ray;
}				t_cub3D;

void game(char *argv);
void cast_rays(t_cub3D *data);
float check_angle(float angle);
void instal_the_wall(t_cub3D *data, int ray);

#endif
