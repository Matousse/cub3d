# Colors for pretty output
GRAY		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
RESET		= \033[0m

# Project configuration
NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
DEBUGFLAGS	= -g

# Directories
SRC_DIR		= ./src
OBJ_DIR		= ./.obj
INC_DIR		= ./includes
MLX_DIR		= includes/minilibx-linux

# Libraries
LIBFT		= $(INC_DIR)/libft/libft.a
PRINTF		= $(INC_DIR)/ft_printf/libftprintf.a
GNL			= $(INC_DIR)/get_next_line/get_next_line.a

# MLX configuration
MLX_LIB		= -L$(MLX_DIR) -lmlx
MLX_FLAGS	= -lXext -lX11 -lm -lz

# Source files
PARSING_SRC	= src/parsing/arg_verif.c \
			  src/parsing/parsing.c \
			  src/parsing/map_init.c \
			  src/parsing/parsing_utils.c \
			  src/parsing/free_parsing.c \
			  src/parsing/map_check1.c \
			  src/parsing/map_check2.c

RAYCAST_SRC	= src/raycasting/raycasting.c \
			  src/raycasting/cleanup.c \
			  src/raycasting/end.c \
			  src/raycasting/load_textures.c

INIT_SRC	= src/init/player_init.c \
			  src/init/initialization.c \

HOOKS_SRC	= src/hooks/hooks.c \
			  src/hooks/movements.c


MAIN_SRC	= $(SRC_DIR)/main.c

# Combine all sources
SRCS		= $(MAIN_SRC) $(PARSING_SRC) $(RAYCAST_SRC) $(INIT_SRC) $(HOOKS_SRC)

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include directories
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)

# Additional flags
LDFLAGS		= -lreadline

# Main targets
all: pre_build $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) $(LDFLAGS)
	@echo
	@echo "$(GREEN) █████╗ ██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "$(GREEN)██╔══██╗██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "$(GREEN)██║  ╚═╝██║   ██║██████╦╝ █████╔╝██║  ██║"
	@echo "$(GREEN)██║  ██╗██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "$(GREEN)╚█████╔╝╚██████╔╝██████╦╝██████╔╝██████╔╝"
	@echo "$(GREEN) ╚════╝  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Libraries
$(LIBFT):
	@echo "$(YELLOW)Making libft...$(RESET)"
	@make bonus --no-print-directory -C $(INC_DIR)/libft

$(PRINTF):
	@echo "$(YELLOW)Making printf...$(RESET)"
	@make --no-print-directory -C $(INC_DIR)/ft_printf

$(GNL):
	@echo "$(YELLOW)Making GNL...$(RESET)"
	@make --no-print-directory -C $(INC_DIR)/get_next_line

# Utility targets
pre_build:
	@echo "$(BLUE)Starting build process...$(RESET)"

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean --no-print-directory -C $(INC_DIR)/libft
	@make clean --no-print-directory -C $(INC_DIR)/ft_printf
	@make clean --no-print-directory -C $(INC_DIR)/get_next_line

fclean: clean
	@echo "$(RED)Cleaning everything...$(RESET)"
	@rm -f $(NAME)
	@make fclean --no-print-directory -C $(INC_DIR)/libft
	@make fclean --no-print-directory -C $(INC_DIR)/ft_printf
	@make fclean --no-print-directory -C $(INC_DIR)/get_next_line

re: fclean all

.PHONY: all clean fclean re debug pre_build
