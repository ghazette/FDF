# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/01 16:40:49 by ghazette     #+#   ##    ##    #+#        #
#    Updated: 2018/03/01 18:07:59 by ghazette    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fdf

SRCS =		srcs/main.c\
			srcs/check.c\
			srcs/color.c\
			srcs/dealkey.c\
			srcs/line.c\
			srcs/map_update.c\
			srcs/mlx.c\
			srcs/parse_fdf.c\
			srcs/z_modifier.c\
			srcs/display.c

HEADERS = 	libft/includes/libft.h includes/fdf.h minilibx_macos/mlx.h

LIBFT =		libft/libft.a

MLX	  =		minilibx_macos/libmlx.a

CFLAGS = 	-Wall -Werror -Wextra -O3

FRAMEWORK = -framework OpenGL -framework AppKit

OBJS = 	$(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(FRAMEWORK) -o $(NAME)

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c -o $@ $<

$(MLX):
	make -C minilibx_macos

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C minilibx_macos clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C minilibx_macos fclean

re : fclean all

.PHONY: all clean fclean re
