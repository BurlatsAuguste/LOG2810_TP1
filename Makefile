all:TP1

TP1: TP1.o Sommet.o Arc.o Vehicule.o Graphe.o Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp
	g++ -Wall TP1.o -o TP1 

Sommet.o: Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp 
	g++ -Wall -c Sommet.cpp -o Sommet.o

Arc.o: Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp
	g++ -Wall -c Arc.cpp -o Arc.o

Vehicule.o: Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp 
	g++ -Wall -c Vehicule.cpp -o Vehicule.o

Graphe.o: Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp
	g++ -Wall -c Graphe.cpp -o Graphe.o

TP1.o: Arc.hpp Sommet.hpp Graphe.hpp Vehicule.hpp 
	g++ -Wall -c TP1.cpp -o TP1.o

clean:
	rm -f TP1 *.o