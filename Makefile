
# Compiler
CC = cc

# Compiler flags
CFLAGS =  -I includes -I libft -g -Wall -Wextra -Werror

# Executable Name
NAME = minishell

#$(wildcard parsing/*.c execution/*.c execution/builtins/*.c)

# Source Files (all .c files in the current directory)
SRCS = main.c free_structs.c parsing/arg_converter.c parsing/arg_converter2.c \
	parsing/count_delimiter.c parsing/envp.c parsing/envp2.c parsing/error.c \
	parsing/error2.c parsing/splitting_args.c parsing/splitting_args2.c \
	parsing/struct_filler.c parsing/typer.c execution/execution.c execution/cleanup.c execution/commands.c \
	execution/heredoc.c execution/pipes.c execution/redirections.c execution/signals.c \
	execution/utils.c execution/utils2.c execution/builtins/cd.c execution/builtins/echo.c \
	execution/builtins/env.c execution/builtins/exit.c execution/builtins/export.c \
	execution/builtins/pwd.c execution/builtins/unset.c execution/builtins/utils.c 

# Object Files
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_LNK = -L$(LIBFT_DIR) -lft

# Default target
all: $(LIBFT_LIB) $(NAME)

# Build executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LNK) -lreadline

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build Libft
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

# Remove executables and object files
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
