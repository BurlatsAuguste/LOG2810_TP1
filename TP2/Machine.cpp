#include <string>
#include "Machine.h"

using namespace std;


Machine::Machine(string mot)
{
	length = mot.length();
	if (length > 0)
	{
		state* current = new state(mot.at(0));
		state* prev = current;
		for (size_t i = 1; i < length; i++)
		{
			state* actual = new state(mot.at(i));
			prev->setNext(actual);
			prev = actual;
		}
		actual->setNext(current);
	}
}

int Machine::next(char let)
{
	char let2 = current->getLet();
	current = current->getNext();
	return let == let2;
}

int Machine::errors(string mot)
{
	if (mot.length() != length)
		return -1;
	int ans = 0;
	for (size_t i = 0; i < mot.length(); i++)
	{
		ans += next(mot.at(i));
	}
	return ans;
}