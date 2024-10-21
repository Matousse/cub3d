CC			= cc
CFLAGS 		= -Wall -Wextra -Werror
DEBUGFLAGS	= -g
LIBFT		= ./libft/libft.a

SRC_DIR		= ./src
OBJ_DIR		= ./.obj
INC_DIR		= ./includes

MLX_DIR 	= /home/dmathis/42cursus/42_utils/mlx
MLX_LIB 	= -L$(MLX_DIR) -lmlx
MLX_FLAGS 	= -lXext -lX11 -lm -lz

SRC_FILES	= $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -name '*.c'))
MAIN_SRC	= $(SRC_DIR)/main.c

SRCS		= $(SRC_FILES) $(MAIN_SRC)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME		= cub3d

INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)

LDFLAGS		= -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

clean:
	rm -rf $(OBJ_DIR)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

$(LIBFT):
	make -C ./libft

.PHONY: all clean fclean re debug
