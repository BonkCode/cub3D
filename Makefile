# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/01 17:01:13 by rtrant            #+#    #+#              #
#    Updated: 2020/09/04 17:46:58 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c colors.c drawing/draw_rect.c vector_funcs/vector2.c \
drawing/draw_line.c drawing/my_mlx_pixel_put.c \
raycast.c distance.c file_to_image.c draw_sprites.c drawing/draw_game.c \
movement.c parsing/main_config.c parsing/check_argc.c parsing/parse.c parsing/parse_utils.c parsing/parce_line.c parsing/parce_map.c \
parsing/config_error.c parsing/validation.c parsing/final_validation.c screenshot.c drawing_utils.c
CFLAGS			= -O3 -I. -Wall -Wextra -Werror -Iparsing -Imlx -Iparsing/libft
CC				= gcc
MLX				= libmlx.dylib
LIBS			= -lmlx -framework OpenGL -framework AppKit -lm libft.a libmlx.dylib
LIBFT			= libft.a
NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS) $(LIBFT)
				gcc ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

$(LIBFT):
				$(MAKE) -C parsing/libft
				mv parsing/libft/$(LIBFT) .

$(MLX):
				$(MAKE) -C mlx
				mv mlx/$(MLX) .

clean:
				$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re