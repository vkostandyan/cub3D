NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
CC = cc #-fsanitize=address

SRCS = main.c

PARSING = 	parse.c \
			error.c \
			colors.c \
			getter.c \
			helpers.c \
			textures.c \
			helpers_2.c \
			array_utils.c \
			map_parsing.c

RAYCASTING = game.c \
			draw_wall.c \
			cast_rays.c \
			movement.c \
			movement2.c \
			textures.c \
			free_and_exit.c \
			drawing.c

GNL = 	get_next_line.c \
		get_next_line_utils.c

LIBFT = ft_bzero.c \
		ft_split.c \
		ft_strdup.c \
		ft_memset.c \
		ft_strlen.c \
		ft_substr.c \
		ft_strstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strtrim.c \
		ft_strlcpy.c \
		ft_putstr_fd.c \
		ft_isdigit.c \
		ft_atoi.c \
		ft_strjoin.c \

SRCS_DIR = ./sources/
LIBFT_DIR = ./sources/libft/
HEADER_DIR = ./headers/
GNL_DIR = ./sources/get_next_line/
PARSING_DIR = ./sources/parsing/
OBJ_DIR = ./objects/
RAY_DIR = ./sources/raycasting/

MLX = -framework OpenGL -framework AppKit -lmlx

SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
PARSING := $(addprefix $(PARSING_DIR), $(PARSING))
RAYCASTING := $(addprefix $(RAY_DIR), $(RAYCASTING))
GNL := $(addprefix $(GNL_DIR), $(GNL))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
SRCS := $(SRCS) $(PARSING) $(RAYCASTING) $(GNL) $(LIBFT)
OBJS := $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(MLX) -I$(HEADER_DIR) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
