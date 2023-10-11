NAME		=	ircserv

COMPILER	=	c++

CPPFLAG		=	-Wall -Wextra -Werror -std=c++98 -g3

INCS		=	incs/Irc.hpp \
			incs/Server.hpp \

SRCS		=	srcs/main.cpp \
			srcs/Server.cpp \

OBJS		=	$(SRCS:.cpp=.o)

RM			=	rm -rf

.cpp.o:
			${COMPILER} ${CFLAGS} -c $< -o $(<:.cpp=.o)

all:		$(NAME)

$(NAME):	$(INCS) $(OBJS)
		$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

