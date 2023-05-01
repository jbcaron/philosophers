# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 13:18:42 by jcaron            #+#    #+#              #
#    Updated: 2023/05/01 13:48:12 by jcaron           ###   ########.fr        #
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
CPPFLAGS := -I$(INC_DIR)
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
    rm -rv $(OBJ_DIR)

fclean: clean
	rm -rv $(BIN_DIR)

-include $(OBJ:.o=.d)