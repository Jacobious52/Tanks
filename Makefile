CPPFLAGS = -std=c++98 -pedantic -Wall
SOURCES	= ConsoleTools.cpp GameView.cpp IntroView.cpp EndView.cpp MutableArray.cpp Point.cpp Sprite.cpp StringTools.cpp Terrain.cpp TextureTools.cpp Timer.cpp Bullet.cpp View.cpp Tank.cpp DebugView.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)

all: game test

game: $(OBJECTS) Game.cpp
	g++ $(CPPFLAGS) -o $@ $^

test: $(OBJECTS) Test.cpp
	g++ $(CPPFLAGS) -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

clean:
	-rm -rf *.o game.dSYM test.dSYM game test

#DEBUG

debug: CPPFLAGS += -ggdb
debug: game test
