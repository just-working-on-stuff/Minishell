NAME    = minishell
HEADER  = ./include
LIBFT   = libft/libft.a
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g -I $(HEADER)

# Readline config (Vagrant setup)
RLDIR   = -L/opt/vagrant/embedded/lib
RLINC   = -I/opt/vagrant/embedded/include
RLFLAGS = -lreadline -lhistory

CORE    = src/core
SRCS    = $(CORE)/main.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(RLINC) $(OBJS) $(LIBFT) $(RLDIR) $(RLFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(RLINC) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
