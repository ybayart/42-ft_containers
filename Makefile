SRC			=	main \
				main_list \
				main_vector \
				main_map

INC			=	utils

SRCS		= $(addsuffix .cpp, ${SRC})

INCS		= $(addsuffix .hpp, ${INC})

OBJS		= ${SRCS:.cpp=.o}

NAME		= containers

CC			= clang++
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -std=c++98

.cpp.o:
			${CC} ${CFLAGS} -D NAMESPACE=ft -c $< -o ${<:.cpp=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -D NAMESPACE=ft

std:		fclean
			${CC} ${CFLAGS} -o ${NAME} ${SRCS} -D NAMESPACE=std

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
