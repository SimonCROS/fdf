LINUX				:= 1

# Folders

override BIN		:= bin
override SRC		:= src
override INC		:= includes

# Libraries

override LIBFT_DIR	:= libft
override LIBFT		:= libft.a
ifeq ($(LINUX),0)
override MINILIBX_DIR	:= minilibx-macos
override MINILIBX		:= libmlx.dylib
else
override MINILIBX_DIR	:= minilibx-linux
override MINILIBX		:= libmlx.a
endif

# Properties

NAME				= fdf

# Commands

override CC			:= gcc
override RM			:= rm -rf
override CFLAGS		:= -Wall -Wextra -Werror -O3
override INCLUDES	:= -I$(INC) -I$(LIBFT_DIR)/$(INC) -I$(MINILIBX_DIR)

# Sources

override SRCS		:=									\
				main.c									\
				exit.c									\
				camera.c								\
				parsing/parser.c						\
				parsing/reader.c						\
				parsing/gnl/get_next_line.c				\
				parsing/gnl/get_next_line_utils.c		\
				engine/project.c						\
				engine/renderer.c						\
				impl/mlx/image.c						\
				impl/mlx/init.c							\
				impl/mlx/game.c							\
				impl/mlx/window.c						\
				impl/mlx/refresh.c						\
				impl/mlx/hook/key_hook.c				\
				impl/mlx/hook/mouse_hook.c				\
				impl/mlx/hook/close_hook.c				\
				impl/mlx/event/on_scroll.c				\
				util/logs.c								\
				util/utils.c							\
				graphic/vector3f/add.c					\
				graphic/vector3f/angle.c				\
				graphic/vector3f/cross.c				\
				graphic/vector3f/distance.c				\
				graphic/vector3f/div.c					\
				graphic/vector3f/negate.c				\
				graphic/vector3f/dot.c					\
				graphic/vector3f/length.c				\
				graphic/vector3f/mul.c					\
				graphic/vector3f/rotate.c				\
				graphic/vector3f/new.c					\
				graphic/vector3f/normalize.c			\
				graphic/vector3f/set.c					\
				graphic/vector3f/sub.c					\
				graphic/vector3f/deserialize.c			\
				graphic/quadric/resolve.c				\
				graphic/quadric/resolve2.c				\
				graphic/matrix/init.c					\
				graphic/matrix/mul.c					\
				graphic/matrix/inverse.c				\
				graphic/matrix/determin.c				\
				graphic/bounding_box/new.c				\
				graphic/bounding_box/intersecions.c		\
				graphic/line/new.c						\
				graphic/line/draw_line.c				\

override OBJS		:= $(addprefix $(BIN)/, $(SRCS:.c=.o))

override HEADERS	:= $(addprefix $(INC)/,				\
				fdf.h									\
				graphics.h								\
				)

LIBRARIES	:= -lpthread
ifeq ($(LINUX),1)
LIBRARIES	+= -lm -lXext -lX11
endif

all:		libs $(NAME)

libs:
			$(MAKE) -C $(LIBFT_DIR)
			ln -sf $(LIBFT_DIR)/$(LIBFT)
			$(MAKE) -C $(MINILIBX_DIR)
			ln -sf $(MINILIBX_DIR)/$(MINILIBX)

bonus:		all

$(BIN)/%.o:	$(SRC)/%.c $(HEADERS)
			@mkdir -p $(dir $@);
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT) $(MINILIBX)
			$(CC) $(CFLAGS) $(OBJS) $(MINILIBX) $(LIBFT) -o $(NAME) $(LIBRARIES)

clean:
			$(RM) $(OBJS)
			find $(BIN) -type d -empty -delete
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(MINILIBX)
			$(MAKE) -C $(MINILIBX_DIR) clean

re:			fclean all

.PHONY:		all libs bonus clean fclean re
