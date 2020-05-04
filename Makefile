SRC			=	main

SRCS		= $(addsuffix .cpp, ${SRC})

OBJS		= ${SRCS:.cpp=.o}

NAME		= list

CC			= clang++
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

.cpp.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
