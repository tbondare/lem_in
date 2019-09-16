# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbondare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 13:47:53 by tbondare          #+#    #+#              #
#    Updated: 2019/09/16 18:39:11 by tbondare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

SRC = ft_isalpha.c ft_memchr.c ft_putchar.c ft_strcpy.c	ft_strncpy.c ft_toupper.c ft_isascii.c ft_memcmp.c ft_putstr.c ft_strdup.c ft_strnstr.c ft_atoi.c ft_isdigit.c ft_memcpy.c ft_strcat.c ft_strlcat.c ft_strrchr.c ft_bzero.c ft_isprint.c ft_memmove.c ft_strchr.c ft_strlen.c ft_strstr.c ft_isalnum.c ft_memccpy.c ft_memset.c ft_strcmp.c ft_strncat.c ft_tolower.c ft_strncmp.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_putendl.c ft_itoa.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_sqrt.c ft_isspace.c ft_lstcnt.c ft_lstaddend.c ft_lstrvrs.c get_next_line.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
		make -C ./ft_printf
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	gcc -Wall -Werror -Wextra -c $< -o $@ -I $(INC_DIR)

clean:
	make clean -C ./ft_printf
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./ft_printf
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

vpath %.c $(SRC_DIR)
