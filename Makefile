CC := cc

NAME := fdf
override CFLAGS += -Wall -Wextra -Werror -mavx2
CPPFLAGS := -Ilibft/include
override LDFLAGS += -lXext -lX11 -lmlx -lm
HEADERS := fdf.h
SRC := main.c matrix4.c handlers.c transformation.c transformation_rotation.c \
	   transformation_update.c transformation_perspective.c ft_strntoi.c \
	   parse.c realloc.c parse_chunk.c fdf.c render.c fdf_init_edges.c \
	   transformation_rview.c bresenham.c render_string.c time.c \
	   transformation_update_projection.c
OBJS := $(SRC:.c=.o)
LIBFT := libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re prof
