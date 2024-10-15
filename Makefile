CC = cc
CFLAGS = #-Wall -Wextra -Werror 

# CFLAGS = -O2
# CFLAGS += -Wpedantic

SRCS = 	draw.c hooks_handler.c main.c player.c raycast.c utils.c raycasting/wall.c raycasting/utils.c mouse_handler.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d
MLX_DIR = minilibx_opengl
INC = -I $(MLX_DIR) -I .
HEADERS = cub3d.h $(MLX_DIR)/mlx.h 
LINKERS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit #-g -fsanitize=address

all: $(NAME) 

$(NAME): $(OBJS) mlx
	$(CC) $(OBJS) $(INC) $(LINKERS) -o $(NAME) 
	@echo "compiling the mandatory part"

mlx:
	make -C $(MLX_DIR)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS) 
	@echo "clean the objects files"

fclean: clean
	@rm -rf $(NAME) 
	@echo "clean the executable files"
