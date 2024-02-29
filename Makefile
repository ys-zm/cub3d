######################
# OS Dependent flags #
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
RUN_CMD		:= ./$(NAME) test_maps/valid_tex.cub
# RUN_CMD		:= ./$(NAME) test_maps/small.cub

# CFLAGS		+= -Wall -Wextra -Werror
# CFLAGS		+= -Wall -Wextra
CFLAGS		+= -g -fsanitize=address
# CFLAGS		+= -g
CFLAGS		+= -Ofast -flto -march=native -fno-fast-math

LIBFT		:=	libft/build/libft.a
LIBMLX		:=	MLX42/build/libmlx42.a

IFLAGS		:= -Ilibft/include -Iinclude -IMLX42/include

SRC_DIR		:=	src
	
SRCS	= 		parser/check_elements.c \
				parser/parse_elements.c \
				parser/parse_textures.c \
				parser/parser.c	\
				parser/check_colors.c \
				parser/lexer.c \
				parser/lexer_utils.c \
				parser/map_lexer.c \
				parser/map_utils.c \
				parser/map_checker.c \
				parser/map_parser.c \
				parser/sprite_parser.c \
				parser/skip_utils.c \
				parser/double_utils.c \
				parser/map_access_utils.c \
				parser/parser_fill.c \
				parser/lexer_test_utils.c \
				parser/door_parser.c \
				utils/error.c \
				utils/free.c \
				utils/colors.c \
				game/game.c \
				game/game_init.c \
				game/draw.c \
				game/keys.c \
				game/player.c \
				game/raycaster/raycaster.c \
				game/raycaster/floorcaster.c \
				renderer/font_renderer.c \
				game/sprite.c \
				game/world.c \
				game/sprite_calc.c \
				game/sprite_render.c \
				game/sprite_sort.c \
				game/sort_utils.c \
				renderer/render_minimap.c \
				renderer/render_viewport.c \
				renderer/pixel_picker.c \
				renderer/draw_func.c \
				vector/vec2i.c \
				vector/vec_utils.c \
				cub3d.c \
				test_utils.c \
				timer.c \
				vector/vec2d_sum.c \
				vector/vec2d_calc.c \
				init/set_textures.c


HEADER_DIR	:=	include
HEADERS 	:=	meta.h \
				timer.h \
				test_utils.h \
				vector.h \
				error.h

OBJ_DIR		:=	obj


TEST_L_FLAGS	:= -L ~/.capt/root/usr/lib/x86_64-linux-gnu
TEST_I_FLAGS	:= -I ~/.capt/root/usr/include
TEST_SRCS	:= 	test_parser.c
TEST		:=	tests
TEST_SRCS	:=	$(addprefix $(TEST)/, $(TEST_SRCS))
TEST_BINS	:=	$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TEST_SRCS))

SRCS 		:=	$(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS 	:=	$(addprefix $(HEADER_DIR)/, $(HEADERS))


OBJS 		:=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJ_DIRS 	:=	$(dir $(OBJS))

.PHONY: make_libs

all: 
	# $(MAKE) make_libs -j4
	$(MAKE) make_libs 
	# $(MAKE) $(NAME) -j4
	$(MAKE) $(NAME) 

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

clean:
	rm -rf $(OBJ_DIR)

tclean:
	rm -rf $(TEST)/bin

fclean: clean tclean
	$(MAKE) -C MLX42/build clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all

run: all
	$(RUN_CMD)

compile_commands: fclean
	cp MLX42/build/compile_commands.json .
	$(MAKE) | compiledb

norm:
	norminette libft include src

$(TEST)/bin:
	mkdir $@

$(TEST)/bin/%: $(TEST)/%.c $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(TEST_I_FLAGS) $(TEST_L_FLAGS) $(MLX_CFLAGS) $< $(OBJS) $(LIBFT) $(LIBMLX) -o $@ -lcriterion 

test: make_libs $(OBJS) $(TEST)/bin $(TEST_BINS)
	for test in $(TEST_BINS) ; do ./$$test -j1 ; done
