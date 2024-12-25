NAME = cub3D
CFLAGS = -Wall -Wextra -Werror 
CC = cc #-fsanitize=address
SRCS =	main.c

# HEADER = 	

# VALIDATION = 

# GAME = 	

# LIBFT =  

# GNL = 	 

MLX = -framework OpenGL -framework AppKit -lmlx

SRCS_DIR = ./sources/
# HEADER_DIR = ./includes/
# LIBFT_DIR = ./sources/libft/
# GNL_DIR = ./sources/get_next_line/
# VALIDATION_DIR = ./sources/validation/
# GAME_DIR = ./sources/game/


SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
# HEADER := $(addprefix $(HEADER_DIR), $(HEADER)) 
# LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
# GNL := $(addprefix $(GNL_DIR), $(GNL))
# VALIDATION := $(addprefix $(VALIDATION_DIR), $(VALIDATION))
# OPERATIONS := $(addprefix $(OPERATIONS_DIR), $(OPERATIONS))
# GAME := $(addprefix $(GAME_DIR), $(GAME))

# SRCS += $(LIBFT)
# SRCS += $(GNL)
# SRCS += $(VALIDATION)
# SRCS += $(GAME)


OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} Makefile 
	@${CC} ${CFLAGS}  ${OBJS} ${MLX} -o ${NAME}

.c.o:
	$(CC) $(CFLAGS)  -Imlx -c $< -o $(<:.c=.o)

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re

