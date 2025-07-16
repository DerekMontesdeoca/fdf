CC := cc

NAME := fdf
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS := -Ilibft/include
LDFLAGS += -lXext -lX11 -lmlx -lm
HEADERS := fdf.h
SRC := main.c matrix4.c handlers.c transformation.c transformation_rotation.c \
	   transformation_update.c transformation_perspective.c ft_strntoi.c \
	   parse.c realloc.c parse_buffer.c
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

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
