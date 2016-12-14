SOURCES=main.cpp player.cpp nonplayer.cpp triangle.cpp door.cpp
FLAGS=-o game -lncurses
game: $(SOURCES)
	g++ $(SOURCES) $(FLAGS)

clean:
	rm game
