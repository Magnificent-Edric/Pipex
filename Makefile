_PIPEX_	=	\
		pipex.c \
		diffrent_child.c \
		some_proc.c \

_PIPEX_BONUS_ =		\
		pipex_bonus.c \
		call_child.c \
		creat_pipes.c \
		error.c \
		file_open.c \
		here_doc.c \

_LIBFT_ =		\
		ft_split.c \
		ft_strlen.c \
		ft_strdel.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_free_arr.c \
		ft_strjoin.c \
		ft_substr.c \
		ft_strncmp.c \


_GET_NEXT_LINE_ =	\
		get_next_line.c \
		get_next_line_utils.c \

PIPEX_BONUS = ${addprefix bonus/, ${_PIPEX_BONUS_}}
PIPEX		= ${addprefix src/, ${_PIPEX_}}
LIBFT		= ${addprefix some_func/, ${_LIBFT_}}
GNL			= ${addprefix get_next_line/, ${_GET_NEXT_LINE_}}

PIPEX		+=  ${LIBFT}
PIPEX_BONUS += ${LIBFT}
PIPEX_BONUS += ${GNL}

OBJ = ${PIPEX:.c=.o}
BONUS_OBJ = ${PIPEX_BONUS:.c=.o}

DEP = ${OBJ:.o=.d}
BONUS_DEP = ${BONUS_OBJ:.o=.d}

NAME			= pipex
BONUS_NAME		= pipex_bonus
INDIR			= include
CC				= gcc
CCFLAGS			= -Leaks -Wall -Werror -Wextra -g
CPPFLAGS		= -MMD -I./${INDIR}

all:	${NAME}

${NAME}:	${OBJ}
	${CC} ${CCFLAGS} ${OBJ} -o ${NAME}

bonus:	${BONUS_NAME}

${BONUS_NAME}:	${BONUS_OBJ}
	${CC} ${CCFLAGS} ${BONUS_OBJ} -o ${BONUS_NAME}

clean:
	${RM} ${DEP} ${BONUS_DEP} ${OBJ} ${BONUS_OBJ} 

fclean:		clean
	${RM} ${NAME} ${BONUS_NAME}

re:		fclean all
re_b:	fclean bonus

.PHONY:	all bonus clean fclean re

-include ${DEP}
-include ${BONUS_DEP}