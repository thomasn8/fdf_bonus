SRCS		= 	main.c						\
				create_coordinates.c		\
				cpy_coordinates.c			\
				map_validation.c			\
				map_validation_error_msg.c	\
				set_window_and_image.c		\
				print_dimensions_infos.c	\
				isometric_transformations.c	\
				center_coordinates.c		\
				get_coordinates_1.c			\
				color_points.c				\
				get_coordinates_2.c			\
				check_limits.c				\
				draw.c						\
				color_lines.c				\
				my_events.c					\
				scale_z.c					\
				draw_black.c				\

OBJS		= ${SRCS:.c=.o}

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L. -lft

MINILIBX_DIR	= mlx
MINILIBX_A		= libmlx.a
MINILIBX		= -L. -lmlx -framework OpenGL -framework AppKit

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= fdf
RM			= rm -f


all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR}/
			cp ${LIBFT_DIR}/$(LIBFT_A) .
			make --silent -C ${MINILIBX_DIR}/
			cp ${MINILIBX_DIR}/$(MINILIBX_A) .
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIBFT) $(MINILIBX)

clean:
			${RM} ${OBJS}
			make --silent -C ${LIBFT_DIR} clean
			make --silent -C ${MINILIBX_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT_A}
			${RM} ${MINILIBX_A}
			${RM} ${LIBFT_DIR}/${LIBFT_A}

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run
