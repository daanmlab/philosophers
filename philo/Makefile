CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR)
NAME = philo

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj


SRC_FILES =  	$(SRC_DIR)/main.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/philo.c \
				$(SRC_DIR)/philo2.c \
				$(SRC_DIR)/routines.c \
				$(SRC_DIR)/observer.c


OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBFT)

# Make sure dir exists
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	clear
	valgrind --leak-check=full ./$(NAME)

clean:
	@rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ]; then 		rm -rf $(OBJ_DIR); 	fi

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re libft

