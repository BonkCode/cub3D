SRCS = main.c colors.c drawing/draw_rect.c vector_funcs/vector2.c drawing/draw_line.c drawing/my_mlx_pixel_put.c \
drawing/test_line.c raycast.c distance.c
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
CC				= gcc
MLX				= libmlx.a
LIBS			= -lmlx -framework OpenGL -framework AppKit -lm

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re