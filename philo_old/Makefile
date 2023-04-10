# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 16:23:55 by jcaron            #+#    #+#              #
#    Updated: 2023/03/06 16:48:03 by jcaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR		=	./src/

SRC			=	$(SRC_DIR)main.c

BIN_DIR		=	./bin/

INC_D		=	./include/

OBJ 		=	$(SRC:$(SRC_DIR)%.c=$(BIN_DIR)%.o)

CC			=	clang

CFLAG		=	-Wall -Wextra

LIBFLAG		=	-lpthread

NAME		=	philo

$(BIN_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAG) -I$(INC_D) -c $< -o $@
	@echo "***compilation of '$<' in '$@'***"

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJ)
	@$(CC) $(CFLAG) $(LIBFLAG) $(OBJ) -o $(NAME)

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)


clean:
	@rm -rf $(BIN_DIR) 
	@echo "***delation of all objects files***"

fclean: clean
	@rm -f $(NAME)
	@echo "***delation of binary file***"

re: fclean all

.PHONY: all clean fclean re