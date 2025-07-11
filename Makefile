CC := cc

NAME := fdf
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS :=
LDFLAGS := -lm
HEADERS := fdf.h
SRC := main.c
OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
