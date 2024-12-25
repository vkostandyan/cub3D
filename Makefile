NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
CC = cc #-fsanitize=address

SRCS = main.c

PARSING = 	parse.c \
			utils.c

GNL = 	get_next_line.c \
		get_next_line_utils.c

LIBFT = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_memset.c ft_strlen.c ft_tolower.c ft_toupper.c \
		ft_memcpy.c ft_memmove.c ft_strncmp.c ft_strchr.c ft_strrchr.c \
		ft_strlcpy.c ft_strlcat.c ft_calloc.c ft_strdup.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_striteri.c ft_strmapi.c  ft_split.c \
		ft_atoi.c ft_memchr.c ft_memcmp.c ft_strnstr.c 

SRCS_DIR = ./sources/
LIBFT_DIR = ./sources/libft/
HEADER_DIR = ./headers/
GNL_DIR = ./sources/get_next_line/
PARSING_DIR = ./sources/parsing/
OBJ_DIR = ./objects/

MLX = -framework OpenGL -framework AppKit -lmlx

SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
PARSING := $(addprefix $(PARSING_DIR), $(PARSING))
GNL := $(addprefix $(GNL_DIR), $(GNL))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
SRCS := $(SRCS) $(PARSING) $(GNL) $(LIBFT)

OBJS := $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) $(OBJS) $(MLX) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
