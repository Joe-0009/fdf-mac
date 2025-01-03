NAME = fdf
CC = cc
CFLAGS = -Os -Ofast -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS = fdf_initialization.c \
    fdf_utils.c \
    fdf_events.c \
    fdf_drawing.c \
    fdf_transform.c \
    fdf_map.c \
    main.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
    $(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) libmlx.a $(MLX_FLAGS) -o $@

clean:
    @rm -f $(OBJS)

fclean: clean
    @rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re