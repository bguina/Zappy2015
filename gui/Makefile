DESTDIR=.
NAME=gui
CC=gcc
CXX=g++
CP=cp -r
RM=rm -f

CSOURCES=\

CPPSOURCES=\
		main.cpp\
		GUI.cpp\
		Camera.cpp\
		Connection.cpp\
		GameSession.cpp\
		LoadSession.cpp\
		EndSession.cpp\
		Session.cpp\
		Map.cpp\
		GameInfo.cpp\
		ViewInfo.cpp\
		GameInfoBar.cpp\
		Terminal.cpp\
		PlayerInfo.cpp\
		GraphicsEngine.cpp\
		Egg.cpp\
		Team.cpp\
		Player.cpp\
		ServerCommandsRegistering.cpp\
		ServerCommandFactoryManager.cpp\
		Anim.cpp                \
                ImgAnim.cpp             \
                LayerAnim.cpp           \
                Layer.cpp               \
                PausableClock.cpp

OBJECTS=$(CSOURCES:.c=.o) $(CPPSOURCES:.cpp=.o)

CPPFLAGS=-I../connection/include -Iinclude -g -Wall -Wextra
CFLAGS=
CXXFLAGS=
LDFLAGS=-lpthread -lsfml-graphics -lsfml-window -lsfml-system

export DESTDIR
.PHONY: all clean fclean re

all: $(DESTDIR)/$(NAME)

$(DESTDIR)/$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(DESTDIR)/$(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(DESTDIR)/$(NAME)

re: clean fclean all

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@F)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $(@F)

