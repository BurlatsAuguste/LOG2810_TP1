#pragma once

//#include "state.h"
#include <string>

class Machine {

private:
	
	class state{
private:
	char let;
	state* next;
	size_t length;


public:
	state(char letter, state* n = nullptr) :let(letter), next(n) {};
	state* getNext() { return next; };
	char getLet() { return let; };
	void setNext(state* n) { next = n; }

};
	state* current;


public:
	Machine(std::string mot);
	int next(char let);
	int errors(std::string mot);

};