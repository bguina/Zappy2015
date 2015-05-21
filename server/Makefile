

NAME=		server

SRC=		bags.c			\
		command.c		\
		communication.c		\
		communication_init.c	\
		communication_list.c	\
		client.c		\
		client_msg.c		\
		crequest.c		\
		death.c			\
		expulse.c		\
		food.c			\
		game_requests.c		\
		ia.c			\
		incantation.c		\
		init_game.c		\
		main.c			\
		map_utilities.c		\
		move.c			\
		new_action.c		\
		new_player.c		\
		player_dc.c		\
		player_requests.c	\
		request.c		\
		server.c		\
		signaling.c		\
		voir.c			\
		xfunc.c			\

OBJ=		$(SRC:.c=.o)

CFLAGS=		-W -Wall -Wextra -g

CC=		gcc

RM=		rm -rf

LIBS=		-lm

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all