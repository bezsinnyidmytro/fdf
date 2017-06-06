#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/14 14:47:43 by dbezsinn          #+#    #+#              #
#    Updated: 2017/05/14 14:47:44 by dbezsinn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		fdf

SRC_DIR = 	fdf_src/
FILES =		fdf_main.c
SRC = 		$(addprefix $(SRC_DIR), $(FILES))
OBJ =		$(SRC:.c=.o)

FLAGS = 	-Wall -Werror -Wextra
LIBFT =		libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -L ./libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	gcc -c $(FLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
