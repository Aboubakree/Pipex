NAME = pipex

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRC = main.c pipex.c pipex_utils.c ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_puthex.c\
    ft_printf/ft_putnbr.c ft_printf/ft_putstr.c libft/ft_strjoin.c libft/ft_split.c\
	libft/ft_split_v2.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strlcpy.c libft/ft_strncmp.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all