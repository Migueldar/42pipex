NAME = pipex
SRC = utils.c main.c executer.c list_operations.c
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) 
	make -C libft
	make -C gnl
	gcc libft/libft.a gnl/gnl.a $(OBJ) -o pipex

all: $(NAME)
clean: 
	$(RM) $(OBJ)
fclean: clean 
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re	
