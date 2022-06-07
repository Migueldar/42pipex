NAME = gnl.a
SRC = get_next_line.c get_next_line_utils.c
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
