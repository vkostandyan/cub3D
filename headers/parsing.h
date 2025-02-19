/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:20 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:35:42 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line.h"
# include "libft.h"

# define COLOR_COMMA_ERR "Color values cannot start or end with ','\n"
# define COLOR_RANGE_ERR "Color values should be in a range of 0-255\n"
# define ARG_ERR "\033[1;31mInvalid number of arguments\033[0m\n"
# define FILE_NAME_ERR "\033[1;31mInvalid file name\033[0m\n"
# define FILE_OPEN_ERR "\033[1;31mCan't open file\033[0m\n"
# define CHAR_ERR "\033[1;31mInvalid char in the map\033[0m\n"
# define COIN_ERR "\033[1;31mMap must contain at least 1 coin\033[0m\n"
# define PLAYER_ERR "\033[1;31mMap must contain 1 player\033[0m\n"
# define EXIT_ERR "\033[1;31mMap must contain 1 exit\033[0m\n"
# define FD_ERR "\033[1;31mMap must contain 1 exit\033[0m\n"
# define EMPTY_LINE_ERR "\033[1;31mMap must not have empty spaces\033[0m\n"
# define RECTANGLE_ERR "\033[1;31mMap must be rectangular\033[0m\n"
# define WALL_ERR "\033[1;31mMap must be surrounded by walls\033[0m\n"
# define MALLOC_ERR "\033[1;31mMemory allocation failed\033[0m\n"
# define SIZE_ERR "\033[1;31mMap is larger than screen\033[0m\n"

typedef enum s_err_type
{
	SUCCESS = 0,
	MALLOC = -1,
	DOUBLICATE = -2,
	INVALID_KEY = -3,
	TOO_MANY_VALUES = -4,
	TOO_FEW_VALUES = -5,
	DOUBLE_COMMA = -6,
	EDGE_COMMA = -7,
	INVALID_RANGE = -8,
	INVALID_COLOR_ARGUMENTS = -9
}					t_err_type;

typedef enum s_type
{
	NOT_VALID,
	EMPTY,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}					t_type;

typedef struct s_player_pos
{
	int				x;
	int				y;
	t_type			start_direction;
}					t_player_pos;

typedef struct s_parse
{
	char			**map;
	char			*north;
	char			*west;
	char			*east;
	char			*south;

	t_player_pos	player;

	int				south_fd;
	int				north_fd;
	int				east_fd;
	int				west_fd;

	int				map_height;
	int				map_width;

	int				ceiling_color;
	int				floor_color;
}					t_parse;

t_parse				parse(int argc, char **argv);

// helpers
void				send_error(char *str);
int					is_empty_line(char *str, char *set);
int					char_match(char c, char const *str);
t_type				check_type(char *str);
int					save_textures(t_parse *data, char *str, int type);
void				clean_parsing_data(t_parse *data);
void				decide_error(char *str, t_type type, int status);
int					set_floor(t_parse *data, char *str);
int					set_ceiling(t_parse *data, char *str);
int					get_color(char *str);
int					get_color2(char **split);
int					check_digit(char **split);
void				free_and_set_null(char *str);
char				*ft_join(char const *s1, char const *s2);
void				check_name(int argc, char **argv);
void				check_chars(t_parse *data, char *map);
void				check_walls(t_parse *data);
char				*read_map(int fd);
void				read_and_parse_map(t_parse *data, int fd);
void				get_player_position(t_parse *data);
void				get_map_height_and_width(t_parse *data);
void				send_file_open_error(char *name);
void				get_textures_fds(t_parse *data);
void				write_type(t_type type);
void				write_key(char *str);
void				check_walls_helper(t_parse *data, int i, int j);
void				check_empty_lines(t_parse *data, char *map);

// array utils
void				*free_array(char **str);
void				print_array(char **str);
int					count_array_len(char **str);

#endif