NAME			=	philo

DIR_SRCS		=	srcs/

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c	init.c	misc.c	fork.c	time.c	routine.c actions.c death.c my_lib.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD			=	-Iincludes/ -Ilibft/includes

CC				=	cc

CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread #-fsanitize=thread

MAKEFLAGS		=	--no-print-directory

all				:	${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ${HEAD} -o $(NAME)
	@echo "\033[34;5mphilo\033[0m"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

stop:
	rm -f ${NAME}

.PHONY:	all clean fclean re bonus
# .SILENT:
