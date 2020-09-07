# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/01 17:01:13 by rtrant            #+#    #+#              #
#    Updated: 2020/09/07 16:19:05 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	drawing/draw_rect.c \
		drawing/draw_line.c \
		drawing/my_mlx_pixel_put.c \
		drawing/file_to_image.c \
		drawing/draw_sprites.c \
		drawing/draw_game.c \
		drawing/drawing_utils.c \
		parsing/main_config.c \
		parsing/check_argc.c \
		parsing/parse.c \
		parsing/parse_utils.c \
		parsing/parse_line.c \
		parsing/parse_map.c \
		parsing/config_error.c \
		parsing/validation.c \
		parsing/final_validation.c \
		raycasting/raycast.c \
		raycasting/raycast_get_funcs.c \
		raycasting/drawing_params_setup.c \
		raycasting/stop_raycasting.c \
		vector_funcs/vector2.c \
		game_exit/config_exit.c \
		game_exit/game_exit.c \
		game_exit/game_exit_utils.c \
		main.c \
		colors.c \
		distance.c \
		movement.c \
		screenshot.c \
		utils.c
CFLAGS			= -O3 -I. -Iparsing -Imlx -Iparsing/libft -Iheaders
CC				= gcc
MLX				= libmlx.dylib
LIBS			= -lmlx -framework OpenGL -framework AppKit -lm libft.a libmlx.dylib
LIBFT			= libft.a
NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(LIBFT)
				gcc ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

$(LIBFT):
				$(MAKE) -C parsing/libft
				mv parsing/libft/$(LIBFT) .

$(MLX):
				$(MAKE) -C mlx
				mv mlx/$(MLX) .

clean:
				$(MAKE) -C mlx clean
				$(MAKE) -C parsing/libft clean

fclean:			clean
				rm -f $(NAME) $(MLX) $(LIBFT)

re:				fclean $(NAME)

.PHONY:			all clean fclean re