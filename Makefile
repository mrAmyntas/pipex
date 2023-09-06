NAME = pipex

CC = gcc

FLAGS = -Wall -Werror -Wextra

RM = rm -rf

OBJ_DIR = obj/

SRC_DIR = src/

SRC =	src/ft_pipex.c\
		src/ft_childprocess.c\
		src/utils.c\
		src/utils2.c\
		src/utils3.c

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

HEADER_FILES = include/pipex.h

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
		$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re