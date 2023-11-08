# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                          :+:    :+:              #
#                                                     +:+ +:+         +:+      #
#    By: ivan-mel <ivan-mel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 13:32:22 by jboeve            #+#    #+#              #
#    Updated: 2023/11/08 23:07:58 by joppe         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


######################
# OS Dependend flags #
######################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_CFLAGS = -ldl -lglfw -pthread -lm
else ifeq ($(shell uname -m),arm64)
	MLX_CFLAGS = -L/opt/homebrew/lib -lglfw -framework IOKit -framework Cocoa
else ifeq ($(shell uname -m),x86_64)
	MLX_CFLAGS = -lglfw3 -framework IOKit -framework Cocoa
endif

NAME		:= app
RUN_CMD		:= ./$(NAME)

# CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -Wall -Wextra
# CFLAGS		+= -g -fsanitize=address
# CFLAGS		+= -Ofast -flto -march=native

LIBFT		:=	libft/build/libft.a
LIBMLX		:=	MLX42/build/libmlx42.a

IFLAGS		:= -Ilibft/include -Iinclude -IMLX42/include

SRC_DIR		:=	src
SRCS		:= 	cub3d.c \
				game.c \
				keys.c \
				timer.c

HEADER_DIR	:=	include
HEADERS 	:=	meta.h \
				timer.h

OBJ_DIR		:=	obj


TEST_SRCS	:= 	test.c
TEST		:=	tests
TEST_SRCS	:=	$(addprefix $(TEST)/, $(TEST_SRCS))
TEST_BINS	:=	$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TEST_SRCS))

SRCS 		:=	$(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS 	:=	$(addprefix $(HEADER_DIR)/, $(HEADERS))


OBJS 		:=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJ_DIRS 	:=	$(dir $(OBJS))

.PHONY: make_libs

all: 
	$(MAKE) make_libs -j4
	$(MAKE) $(NAME) -j4

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS) $(SRC_DIR)/main.c
	$(CC) $(SRC_DIR)/main.c $(OBJS) $(LIBFT) $(LIBMLX) $(CFLAGS) $(IFLAGS) $(MLX_CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

make_libs: $(LIBMLX)
	$(MAKE) -C MLX42/build
	$(MAKE) -C libft

MLX42:
	git clone git@github.com:codam-coding-college/MLX42.git

$(LIBMLX): MLX42
	mkdir -p MLX42/build
	cmake MLX42 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B MLX42/build
	make -C MLX42/build -j4
	cp MLX42/build/compile_commands.json .

clean:
	rm -rf $(OBJ_DIR)

tclean:
	rm -rf $(TEST)/bin

fclean: clean tclean
	$(MAKE) -C MLX42/build clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	$(RUN_CMD)

compile_commands: fclean
	$(MAKE) | compiledb

norm:
	norminette libft include src

$(TEST)/bin:
	mkdir $@

$(TEST)/bin/%: $(TEST)/%.c $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $< $(OBJS) $(LIBFT) -o $@ -lcriterion

test: make_libs $(OBJS) $(TEST)/bin $(TEST_BINS)
	for test in $(TEST_BINS) ; do ./$$test -j1 ; done
