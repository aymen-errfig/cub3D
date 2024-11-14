CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = mandatory/game/load_game.c mandatory/game/utils.c mandatory/hooks_handler.c mandatory/main.c mandatory/manage_assests.c mandatory/parsing/get_next_line.c mandatory/parsing/get_next_line_utils.c mandatory/parsing/parse.c mandatory/parsing/parse2.c mandatory/parsing/split.c mandatory/parsing/utils.c mandatory/parsing/utils2.c mandatory/player.c mandatory/raycasting/h_intersection.c mandatory/raycasting/raycast.c mandatory/raycasting/utils.c mandatory/raycasting/v_intersection.c mandatory/raycasting/wall.c mandatory/utils.c mandatory/utils2.c
BONUS_SRCS = bonus/draw.c bonus/game/load_game.c bonus/game/utils.c bonus/hooks_handler.c bonus/main.c bonus/manage_assests.c bonus/mouse_handler.c bonus/parsing/get_next_line.c bonus/parsing/get_next_line_utils.c bonus/parsing/parse.c bonus/parsing/parse2.c bonus/parsing/split.c bonus/parsing/utils.c bonus/parsing/utils2.c bonus/player.c bonus/raycasting/h_intersection.c bonus/raycasting/raycast.c bonus/raycasting/utils.c bonus/raycasting/v_intersection.c bonus/raycasting/wall.c bonus/utils.c bonus/utils2.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
NAME = cub3d
BONUS_N = cub3d_bonus
MLX_DIR = minilibx_opengl
INC = -I $(MLX_DIR) -I .
LIB_HEADER = $(MLX_DIR)/mlx.h
MAN_HEADER = mandatory/cub3d.h
BONUS_HEADER = bonus/cub3d.h
LINKERS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME) $(MLX_DIR)/libmlx.a
bonus: $(BONUS_N) $(MLX_DIR)/libmlx.a


$(NAME): $(OBJS) 
	make -C $(MLX_DIR)
	$(CC) $(OBJS) $(INC) $(LINKERS) -o $(NAME) 
	@echo "\033[32m   ______      __   _____ ____  "
	@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
	@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
	@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
	@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./Cub3D <map.cub> \033[97m"

$(BONUS_N): $(BONUS_OBJS) 
	make -C $(MLX_DIR)
	$(CC) $(BONUS_OBJS) $(INC) $(LINKERS) -o $(BONUS_N) 
	@echo "\033[32m   ______      __   _____ ____  "
	@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
	@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
	@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
	@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./Cub3D <map.cub> \033[97m"

$(MLX_DIR)/libmlx.a: 
	make -C $(MLX_DIR)

mandatory/%.o: mandatory/%.c $(MAN_HEADER) $(LIB_HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus/%.o: bonus/%.c $(BONUS_HEADER) $(LIB_HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	make -C $(MLX_DIR) clean
	@echo "clean the objects files"

fclean: clean
	@rm -rf $(NAME) $(BONUS_N)
	@rm -rf $(MLX_DIR)/libmlx.a 
	@echo "clean the executable files"

