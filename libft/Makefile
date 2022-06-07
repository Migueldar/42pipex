NAME = libft.a
SRC = ft_strlen.c ft_strncmp.c ft_strlcpy.c ft_bzero.c ft_calloc.c ft_substr.c ft_strjoin.c ft_split.c
FLAGS = -Wall -Wextra -Werror
RM = /bin/rm -f
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
