CC = cc
CFLAGS = #-Wall -Wextra -Werror 

# CFLAGS = -O2
# CFLAGS += -Wpedantic

SRCS = 	draw.c hooks_handler.c main.c player.c raycast.c utils.c raycasting/wall.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d
HEADERS = cub3d.h
LINKERS = -lmlx -framework OpenGL -framework AppKit -g -fsanitize=address

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LINKERS) -o $(NAME) 
	@echo "compiling the mandatory part"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS) 
	@echo "clean the objects files"

fclean: clean
	@rm -rf $(NAME) 
	@echo "clean the executable files"
