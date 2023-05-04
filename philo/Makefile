# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 13:18:42 by jcaron            #+#    #+#              #
#    Updated: 2023/05/04 16:34:35 by jcaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := src
OBJ_DIR := objs
BIN_DIR := bin
INC_DIR := include

EXE := $(BIN_DIR)/philo
#SRC := $(wildcard $(SRC_DIR)/*.c)
SRC := $(SRC_DIR)/event_buffer.c \
       $(SRC_DIR)/main.c \
       $(SRC_DIR)/monitor_1.c \
       $(SRC_DIR)/monitor_2.c \
       $(SRC_DIR)/monitor_3.c \
       $(SRC_DIR)/monitor_4.c \
       $(SRC_DIR)/parse_arg.c \
       $(SRC_DIR)/philo.c \
       $(SRC_DIR)/philo_methods_1.c \
       $(SRC_DIR)/philo_methods_2.c \
       $(SRC_DIR)/philo_methods_3.c \
       $(SRC_DIR)/philo_state_machine_actions.c \
       $(SRC_DIR)/philo_state_machine_check.c \
       $(SRC_DIR)/utils_1.c \
       $(SRC_DIR)/utils_2.c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC       := clang
CPPFLAGS := -I$(INC_DIR) -MMD -MP 
CFLAGS   := -Wall -Wextra -Werror -O2
#CFLAGS   := -Wall -Wextra -O2 -g -fsanitize=thread

.PHONY: all clean fclean re

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean
	make all

-include $(OBJ:.o=.d)
