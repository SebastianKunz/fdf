# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skunz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/30 08:39:29 by skunz             #+#    #+#              #
#    Updated: 2018/11/30 08:39:31 by skunz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c get_next_line/get_next_line.c map.c draw.c
OBJ = main.o get_next_line.o map.o  draw.o

all: $(NAME)

$(NAME): lib
	gcc -c $(SRC)
	gcc $(OBJ) $(LIB) -g -L minilibx_macos -lmlx -I minilibx_macos/mlx.h -L get_next_line/libft/ -lft -framework OpenGL -framework AppKit -o $(NAME)

clean: libclean
	/bin/rm -f $(OBJ)

fclean: clean libfclean
	/bin/rm -f $(NAME)

lib:
	make -C get_next_line/libft/ all

libfclean:
	make -C get_next_line/libft/ fclean

libclean:
	make -C get_next_line/libft/ clean

re: fclean all
