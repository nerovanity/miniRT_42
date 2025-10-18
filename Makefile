srcs= main.c utils/ft_split.c utils/get_next_line.c vectors/vec_op2.c vectors/vector_op.c \
	parsing/parse_camera.c parsing/parse_object.c parsing/parse_options.c parsing/parsing.c\
	utils/utils.c utils/utils2.c parsing/parse_light.c camera.c utils/utils3.c objects/cylinder.c\
	objects/cyl_utils.c objects/plan.c mlx_hooks.c lightning.c raytracing.c objects/sphere.c
objs=$(srcs:%.c=%.o)
flags= -Wall -Wextra -Werror 
CC= cc
NAME = miniRT
HEADER = minirt.h 

all: $(NAME)

$(NAME): $(objs)
	$(CC) $(flags) -o $@ $^ -lX11 -lXext -lmlx -lm

%.o: %.c $(HEADER)
	$(CC) $(flags) -c $< -o $@

clean: 
	rm -f $(objs) 

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all