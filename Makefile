# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbondare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 16:35:39 by tbondare          #+#    #+#              #
#    Updated: 2019/09/15 22:28:14 by tbondare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INC = -I ./inc -I ./libft/inc

LIB_DIR = ./libft/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

LIB = $(LIB_DIR)libft.a

CONTR_DIR = $(SRC_DIR)controller/

SRC = ./src/main.c ./src/find_valid_path.c ./src/ft_free_mem.c ./src/helper_f_find_vl_path.c ./src/hlp_f_run_ants.c ./src/hlpr_f_try_read.c ./src/read_data.c ./src/run_ants.c ./src/try_read.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

.PHONY: all clean fclean

%.o: $(CONTR_DIR)%.c
	gcc -Wall -Werror -Wextra -c $< $(INC)

all: $(NAME)
$(NAME):
	make -C $(LIB_DIR)
	gcc -Wall -Werror -Wextra -c $< -o $@ -L ./libft -llibft 
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJ)
fclean: clean
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)
re: fclean all
