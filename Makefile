all:TP1

TP1: TP1.o Sommet.o Arc.o Vehicule.o Graphe.o
	g++ -Wall TP1.o -o TP1 

Sommet.o: Arc.h Sommet.h Graphe.h Vehicule.h 
	g++ -Wall -c Sommet.cpp -o Sommet.o

Arc.o: Arc.h Sommet.h Graphe.h Vehicule.h 
	g++ -Wall -c Arc.cpp -o Arc.o

Vehicule.o: Arc.h Sommet.h Graphe.h Vehicule.h 
	g++ -Wall -c Vehicule.cpp -o Vehicule.o

Graphe.o: Arc.h Sommet.h Graphe.h Vehicule.h
	g++ -Wall -c Graphe.cpp -o Graphe.o

TP1.o: Arc.h Sommet.h Graphe.h Vehicule.h 
	g++ -Wall -c TP1.cpp -o TP1.o