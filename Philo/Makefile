CC = cc
FLAGS = -Wall -Werror -Wextra
FLAG_THREAD = -g -O0 -pthread

NAME = philo

SRC = main.c src/init.c src/monitor.c src/routine.c \
src/utils_1.c src/utils_2.c src/utils_3.c src/free.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

race: $(OBJ)
	$(CC) $(FLAG_THREAD) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re