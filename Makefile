CC := cc

NAME := fdf
override CFLAGS += -Wall -Wextra -Werror -mavx2
CPPFLAGS := -Ilibft/include -Iminilibx-linux
override LDFLAGS += -Lminilibx-linux -lXext -lX11 -lmlx -lm 
HEADERS := fdf.h
SRC := main.c matrix4.c handlers.c transformation.c transformation_rotation.c \
	   transformation_update.c transformation_projection.c ft_strntoi.c \
	   parse.c realloc.c parse_chunk.c fdf.c render.c fdf_init_edges.c \
	   transformation_rview.c bresenham.c render_string.c time.c \
	   matrix4_vector.c projection_ctl.c transformation_utilities.c \
	   fdf_draw_lines.c color.c font.c util.c parse_utils.c
OBJS := $(SRC:.c=.o)
LIBFT := libft/libft.a
MLX := minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT))

$(MLX):
	cd $(dir $(MLX))
	$(MAKE) -C $(dir $(MLX))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(MAKE) -C $(dir $(MLX)) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
