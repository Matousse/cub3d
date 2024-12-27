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
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lXext -lX11 -lm -lz

# Source files
RAYCAST_SRC	= src/raycasting/raycasting.c \

INIT_SRC	= src/init/init.c \

HOOKS_SRC	= src/hooks/hooks.c \

MAIN_SRC	= $(SRC_DIR)/main.c \
				$(SRC_DIR)/cleanup.c \
				$(SRC_DIR)/game_state.c

REN_SRC		= src/rendering/pixels.c \
				src/rendering/textures.c \
				src/rendering/ui.c \
				src/rendering/minimap.c

PARS_SRC	= src/parsing/parsing.c \
				src/parsing/parsing_utils.c \
				src/parsing/map_init.c \
				src/parsing/map_check1.c \
				src/parsing/map_check2.c \
				src/parsing/free_parsing.c \
				src/parsing/arg_verif.c \

# Combine all sources
SRCS		= $(MAIN_SRC) $(RAYCAST_SRC) $(INIT_SRC) $(HOOKS_SRC) $(REN_SRC) $(PARS_SRC)

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include directories
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)

# Additional flags
LDFLAGS		= -lreadline

# Main targets
all: pre_build $(NAME)

# Main compilation
$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(MLX_LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) $(LDFLAGS)
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

$(MLX_LIB):
	@echo "$(YELLOW)Making minilibx...$(RESET)"
	@make --no-print-directory -C $(MLX_DIR) > /dev/null 2>&1

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
	@make clean --no-print-directory -C $(MLX_DIR) > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning everything...$(RESET)"
	@rm -f $(NAME)
	@make fclean --no-print-directory -C $(INC_DIR)/libft
	@make fclean --no-print-directory -C $(INC_DIR)/ft_printf
	@make fclean --no-print-directory -C $(INC_DIR)/get_next_line

re: fclean all

.PHONY: all clean fclean re debug pre_build
