# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vame <vame@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/23 11:23:10 by vame              #+#    #+#              #
#    Updated: 2015/03/10 13:02:18 by vame             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

INC = ./fractol.h

CFLAGS = -Werror -Wextra -Wall -I libft/includes/

LIBX = -lm -L libft/ -lft -L /usr/x11/lib -lmlx -lXext -lX11

TMP = $(INC:.h=.h.gch)

SRC =	./ftol_main.c \
		./ftol_draw.c \
		./ftol_tools.c \
		./ftol_expose.c \
		./ftol_window.c \
		./ftol_keyhook.c \
		./ftol_mousehook.c

BINAIRE = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINAIRE) $(INC)
		@make -C libft/
		gcc -c $(CFLAGS) $(INC) $(SRC)
		gcc -g -o $(NAME) $(BINAIRE) $(LIBX)
		@rm -f $(TMP)

lib :
		@make -C libft/ fclean
		@make -C libft/

clean:
		rm -f $(BINAIRE)
		@make -C libft/ clean

fclean: clean
		rm -f $(NAME)
		@make -C libft/ fclean

re: fclean all

.PHONY: all lib clean fclean re
