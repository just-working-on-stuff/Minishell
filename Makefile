NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# --- Sources / Objects ---
SRCS := srcs/main.c \
        srcs/utils/list_token.c \
		srcs/utils/utils.c \
        srcs/utils/signals.c \
        srcs/utils/signals2.c\
		srcs/exec/run_simple.c\
		srcs/parsing/lexer.c\
		srcs/parsing/lexers_utils.c\
		srcs/parsing/parser_utils.c\
		srcs/parsing/parser.c\
		srcs/parsing/cmd_fd.c\
		srcs/parsing/lexer_quotes.c\
		srcs/parsing/readline_utils.c\
		srcs/parsing/expander.c\
		srcs/parsing/expander_utils.c\
		srcs/builtins/echo.c \
		srcs/builtins/pwd.c \
		srcs/builtins/exit.c \
		srcs/builtins/env.c \
		srcs/builtins/unset.c \
		srcs/builtins/cd.c \
		srcs/builtins/builtins_utils.c \

OBJS := $(SRCS:.c=.o)

# --- Libft ---
LIBFT_DIR   := ./libft
LIBFT       := $(LIBFT_DIR)/libft.a
LIBFT_INC   := -I$(LIBFT_DIR)

# --- Readline (Vagrant path you showed) ---
# Use the *parent* include dir; headers are <readline/readline.h>
READLINE_INC := -I/opt/vagrant/embedded/include
READLINE_LIB := -L/opt/vagrant/embedded/lib -lreadline
# If you still get link errors, try also:
# READLINE_LIB := -L/opt/vagrant/embedded/lib -lreadline -lncurses

INCS        := -I. $(LIBFT_INC) $(READLINE_INC)

# --- Rules ---
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
