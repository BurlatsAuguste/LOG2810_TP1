all:tp2

tp2: tp2.o noeud.o
	g++ -Wall tp2.o noeud.o -o tp2

noeud.o: noeud.cpp noeud.hpp
	g++ -Wall -c noeud.cpp -o noeud.o

tp2.o: tp2.cpp
	g++ -Wall -c tp2.cpp -o tp2.o

clean:
	rm -f tp2 *.o