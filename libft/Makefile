# **************************************************************************** #
#  #
# :::::::: #
#Makefile  :+::+:  #
#  +:+ #
#By: jboeve <jboeve@student.codam.nl> +#+  #
#+#+   #
#Created: 2022/10/17 12:05:02 by jboeve#+##+#  #
#Updated: 2023/08/20 23:17:31 by joppe ########   odam.nl  #
#  #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
OUT_DIR = build

HEADERS = libft.h get_next_line.h
SRCS = $(DIR_LST) $(DIR_STRING) $(DIR_ASCII) \
	   $(DIR_CONVERT) $(DIR_MEM) $(DIR_PUT) \
	   $(DIR_GNL) $(DIR_PRINTF)

DIR_ASCII = 	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c

DIR_CONVERT = 	ft_itoa.c \
			  	ft_atoi.c \
			  	ft_toupper.c \
			  	ft_tolower.c \
			  	ft_atoi_hex.c \
			  	ft_atol.c

DIR_STRING = 	ft_split.c \
				ft_strchr.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strjoin_free.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strcmp_largest.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_strdup.c \
				ft_strlen_2d.c \
				ft_strisempty.c \
				ft_strcmp_largest.c \
				ft_strjoin_free.c

DIR_MEM = 		ft_bzero.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_realloc.c

DIR_PUT = 		ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c

DIR_LST = 		ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
			 	ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

DIR_GNL 	= 	get_next_line.c \
				get_next_line_utils.c

DIR_LST := $(addprefix lst/, $(DIR_LST))
DIR_STRING := $(addprefix str/, $(DIR_STRING))
DIR_ASCII := $(addprefix ascii/, $(DIR_ASCII))
DIR_CONVERT := $(addprefix convert/, $(DIR_CONVERT))
DIR_MEM := $(addprefix mem/, $(DIR_MEM))
DIR_PUT := $(addprefix put/, $(DIR_PUT))
DIR_GNL := $(addprefix gnl/, $(DIR_GNL))

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADERS := $(addprefix $(INC_DIR)/, $(HEADERS))
NAME := $(addprefix $(OUT_DIR)/, $(NAME))

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@mkdir -p $(OUT_DIR)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(OUT_DIR)

re: fclean all
