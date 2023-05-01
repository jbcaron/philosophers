# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 13:18:42 by jcaron            #+#    #+#              #
#    Updated: 2023/05/01 14:48:09 by jcaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := src
OBJ_DIR := objs
BIN_DIR := bin
INC_DIR := include

EXE := $(BIN_DIR)/philo
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC       := clang
CPPFLAGS := -I$(INC_DIR) -MMD -MP
CFLAGS   := -Wall -Wextra

.PHONY: all clean fclean re

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

-include $(OBJ:.o=.d)
