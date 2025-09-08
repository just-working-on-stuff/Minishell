NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra 

SRCS = main.c cd.c /

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

