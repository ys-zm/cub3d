# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: jboeve <jboeve@student.codam.nl>            +#+                       #
#                                                   +#+                        #
#    Created: 2023/11/01 20:05:28 by jboeve        #+#    #+#                  #
#    Updated: 2023/11/01 20:25:43 by jboeve        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = app

######################
# OS Dependend flags #
######################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_CFLAGS = -lglfw -lm
endif
ifeq ($(UNAME_S),Darwin)
	MLX_CFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm
	CFLAGS = -DOS_MAC
endif


# CFLAGS += -Wall -Wextra -Werror
CFLAGS += -Wall -Wextra
# CFLAGS += -g -fsanitize=address
# CFLAGS = -g 
# CFLAGS = -Ofast -flto -march=native


LIBFT = libft/build/libft.a

INC = -Ilibft/include -Iinclude 

SRC_DIR = src
SRCS =	main.c \
		enemy.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADER_DIR = include
HEADERS = meta.h

HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: make_libs

all:
	$(MAKE) make_libs -j4
	$(MAKE) $(NAME) -j4

$(NAME): $(MLX) $(OBJS) $(LIBFT) 
	echo $(MLX_CFLAGS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_CFLAGS) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

make_libs: $(MLX)
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	$(RUN_CMD)

compile_commands: fclean
	$(MAKE) | compiledb

norm:
	norminette libft include src

dre: re
	$(MAKE) -C libft re
