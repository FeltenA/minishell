SRCS	=	lexer/lexer.c\
			lexer/token_list_utils.c\
			lexer/check_error.c\
			lexer/lexer_utils.c\
			error.c\
			main.c\
			free.c

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

LIBFT	= ./libft/libft.a

INC		= -I ./includes -I ./libft

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o:		%.c
		${CC} ${CFLAGS} -c $< -o $@ ${INC}

all:		${LIBFT} ${NAME}

${LIBFT}:
		@make all -C libft
		@make bonus -C libft

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME} ${INC} ${LIBFT} -l readline

clean:
		${RM} ${OBJS}
		@make clean -C libft

fclean:		clean
		${RM} ${NAME}
		@make fclean -C libft

re:		fclean
		make all

.PHONY:		all clean fclean re bonus
