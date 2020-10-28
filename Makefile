all:TP1

TP1: TP1.o Sommet.o Vehicule.o Graphe.o
	g++ -Wall TP1.o Sommet.o Vehicule.o Graphe.o -o TP1

Sommet.o: Sommet.cpp Sommet.hpp
	g++ -Wall -c Sommet.cpp -o Sommet.o

Vehicule.o: Vehicule.cpp Vehicule.hpp
	g++ -Wall -c Vehicule.cpp -o Vehicule.o

Graphe.o: Graphe.cpp Graphe.hpp
	g++ -Wall -c Graphe.cpp -o Graphe.o

TP1.o: TP1.cpp
	g++ -Wall -c TP1.cpp -o TP1.o

clean:
	rm -f TP1 *.o