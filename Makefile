# Colors for pretty output
GRAY		= \033[30m
RED		= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
RESET		= \033[0m

# Project configuration
NAME		= cub3d
NAME_BONUS	= cub3d_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
DEBUGFLAGS	= -g

# Directories
SRC_DIR		= ./mandatory/src
BONUS_SRC_DIR	= ./bonus/src
OBJ_DIR		= ./.obj
INC_DIR		= ./includes
MLX_DIR		= $(INC_DIR)/minilibx-linux

# Libraries
LIBFT		= $(INC_DIR)/libft/libft.a
PRINTF		= $(INC_DIR)/ft_printf/libftprintf.a
GNL		= $(INC_DIR)/get_next_line/get_next_line.a
MLX		= $(MLX_DIR)/libmlx.a

# MLX configuration
MLX_FLAGS	= -L$(MLX_DIR) -lXext -lX11 -lm -lz

# Mandatory source files
RAYCAST_SRC	= $(SRC_DIR)/raycasting/raycasting.c \
		  $(SRC_DIR)/raycasting/raycasting2.c \
		  $(SRC_DIR)/raycasting/raycasting3.c \
		  $(SRC_DIR)/raycasting/raycasting4.c

INIT_SRC	= $(SRC_DIR)/init/init.c \
		  $(SRC_DIR)/init/init2.c

HOOKS_SRC	= $(SRC_DIR)/hooks/hooks.c \
		  $(SRC_DIR)/hooks/hooks2.c

MAIN_SRC	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/cleanup.c

REN_SRC		= $(SRC_DIR)/rendering/pixels.c \
		  $(SRC_DIR)/rendering/textures.c

PARS_SRC	= $(SRC_DIR)/parsing/parsing.c \
		  $(SRC_DIR)/parsing/parsing_utils.c \
		  $(SRC_DIR)/parsing/map_init.c \
		  $(SRC_DIR)/parsing/map_check1.c \
		  $(SRC_DIR)/parsing/map_check2.c \
		  $(SRC_DIR)/parsing/free_parsing.c \
		  $(SRC_DIR)/parsing/arg_verif.c

# Bonus source files
BONUS_RAYCAST_SRC = $(BONUS_SRC_DIR)/raycasting/raycasting_bonus.c \
		    $(BONUS_SRC_DIR)/raycasting/raycasting2_bonus.c \
		    $(BONUS_SRC_DIR)/raycasting/raycasting3_bonus.c \
		    $(BONUS_SRC_DIR)/raycasting/raycasting4_bonus.c

BONUS_INIT_SRC = $(BONUS_SRC_DIR)/init/init_bonus.c \
		 $(BONUS_SRC_DIR)/init/init2_bonus.c

BONUS_HOOKS_SRC = $(BONUS_SRC_DIR)/hooks/hooks_bonus.c \
		  $(BONUS_SRC_DIR)/hooks/hooks2_bonus.c

BONUS_MAIN_SRC = $(BONUS_SRC_DIR)/main_bonus.c \
		 $(BONUS_SRC_DIR)/cleanup_bonus.c

BONUS_REN_SRC = $(BONUS_SRC_DIR)/rendering/pixels_bonus.c \
		$(BONUS_SRC_DIR)/rendering/textures.c \
		$(BONUS_SRC_DIR)/rendering/minimap_bonus.c \
		$(BONUS_SRC_DIR)/rendering/minimap2_bonus.c \
		$(BONUS_SRC_DIR)/rendering/minimap3_bonus.c

BONUS_PARS_SRC = $(BONUS_SRC_DIR)/parsing/parsing_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/parsing_utils_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/map_init_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/map_check1_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/map_check2_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/free_parsing_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/free_parsing2_bonus.c \
		 $(BONUS_SRC_DIR)/parsing/arg_verif_bonus.c

# Combine all sources
SRCS		= $(MAIN_SRC) $(RAYCAST_SRC) $(INIT_SRC) $(HOOKS_SRC) $(REN_SRC) $(PARS_SRC)
BONUS_SRCS	= $(BONUS_MAIN_SRC) $(BONUS_RAYCAST_SRC) $(BONUS_INIT_SRC) $(BONUS_HOOKS_SRC) $(BONUS_REN_SRC) $(BONUS_PARS_SRC)

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:$(BONUS_SRC_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)

# Include directories
INCLUDES	= -I$(INC_DIR)
INCLUDES_BONUS	= -I$(INC_DIR)

# Additional flags
LDFLAGS		= -lreadline

# Main targets
all: pre_build $(NAME)

bonus: pre_build $(NAME_BONUS)

# Main compilation
$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(MLX_FLAGS) -o $(NAME) $(LDFLAGS)
	@echo
	@echo "$(GREEN) █████╗ ██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "$(GREEN)██╔══██╗██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "$(GREEN)██║  ╚═╝██║   ██║██████╦╝ █████╔╝██║  ██║"
	@echo "$(GREEN)██║  ██╗██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "$(GREEN)╚█████╔╝╚██████╔╝██████╦╝██████╔╝██████╔╝"
	@echo "$(GREEN) ╚════╝  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo

$(NAME_BONUS): $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(MLX_FLAGS) -o $(NAME_BONUS) $(LDFLAGS)
	@echo
	@echo "$(GREEN) █████╗ ██╗   ██╗██████╗ ██████╗ ██████╗     ██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗"
	@echo "$(GREEN)██╔══██╗██║   ██║██╔══██╗╚════██╗██╔══██╗    ██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝"
	@echo "$(GREEN)██║  ╚═╝██║   ██║██████╦╝ █████╔╝██║  ██║    ██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗"
	@echo "$(GREEN)██║  ██╗██║   ██║██╔══██╗ ╚═══██╗██║  ██║    ██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║"
	@echo "$(GREEN)╚█████╔╝╚██████╔╝██████╦╝██████╔╝██████╔╝    ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║"
	@echo "$(GREEN) ╚════╝  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝"
	@echo

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

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

$(MLX):
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
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean --no-print-directory -C $(INC_DIR)/libft
	@make fclean --no-print-directory -C $(INC_DIR)/ft_printf
	@make fclean --no-print-directory -C $(INC_DIR)/get_next_line

re: fclean all

.PHONY: all clean fclean re debug pre_build bonus