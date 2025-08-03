NAME = philo

CC = cc -g

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

SRCS = main.c parse.c routine.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)


fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re