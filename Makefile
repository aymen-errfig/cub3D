CC = cc
CFLAGS = -Wall -Wextra -Werror 

# CFLAGS = -O2
# CFLAGS += -Wpedantic

SRCS = 	draw.c game/load_game.c game/utils.c hooks_handler.c main.c manage_assests.c mouse_handler.c parsing/get_next_line.c parsing/get_next_line_utils.c parsing/parse.c parsing/parse2.c parsing/split.c parsing/utils.c player.c raycasting/h_intersection.c raycasting/raycast.c raycasting/utils.c raycasting/v_intersection.c raycasting/wall.c utils.c utils2.c



OBJS = $(SRCS:.c=.o)
NAME = cub3d
MLX_DIR = minilibx_opengl
INC = -I $(MLX_DIR) -I .
HEADERS = cub3d.h $(MLX_DIR)/mlx.h
LINKERS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -g -fsanitize=address

all: $(NAME) $(MLX_DIR)/libmlx.a 

$(NAME): $(OBJS) 
	make -C $(MLX_DIR)
	$(CC) $(OBJS) $(INC) $(LINKERS) -o $(NAME) 
	@echo "\033[32m   ______      __   _____ ____  "
	@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
	@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
	@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
	@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./Cub3D <map.cub> "

$(MLX_DIR)/libmlx.a: 
	make -C $(MLX_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS) 
	make -C $(MLX_DIR) clean
	@echo "clean the objects files"

fclean: clean
	@rm -rf $(NAME) 
	@rm -rf $(MLX_DIR)/libmlx.a 
	@echo "clean the executable files"

