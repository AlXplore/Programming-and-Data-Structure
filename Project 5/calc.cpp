#include "dlist.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class BadInput {};
class NotEnough {};
class Divide0 {};

bool EnoughOperandsCheck(Dlist<int> &dlist, int size_need)
{
	int size = 0;
	if (dlist.isEmpty())
		size = 0;
	else
	{
		int *a = dlist.removeFront();
		if (dlist.isEmpty())
		{
			size = 1;
			dlist.insertFront(a);
		}
		else
		{
			size = 2;
			dlist.insertFront(a);
		}
	}
	if (size < size_need)
		return false;
	else
		return true;
}

void Plus(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist, 2))
		throw ne;
	int *a = dlist.removeFront();
	int *b = dlist.removeFront();
	int *c = new int;
	*c = *a + *b;
	dlist.insertFront(c);
	delete a;
	delete b;
}

void Minus(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist, 2))
		throw ne;
	int *a = dlist.removeFront();
	int *b = dlist.removeFront();
	int *c = new int;
	*c = *b - *a;
	dlist.insertFront(c);
	delete a;
	delete b;
}

void Multiple(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist,2))
		throw ne;
	int *a = dlist.removeFront();
	int *b = dlist.removeFront();
	int *c = new int;
	*c = (*b) * (*a);
	dlist.insertFront(c);
	delete a;
	delete b;
}

void Divide(Dlist<int> &dlist)
{
	NotEnough ne;
	Divide0 d0;
	if (!EnoughOperandsCheck(dlist,2))
		throw ne;
	int *a = dlist.removeFront();
	if (*a == 0)
		throw d0;
	int *b = dlist.removeFront();
	int *c = new int;
	*c = (*b) / (*a);
	dlist.insertFront(c);
	delete a;
	delete b;
}

void Negate(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist,1))
		throw ne;
	int *a = dlist.removeFront();
	int *b = new int;
	*b = -*a;
	dlist.insertFront(b);
	delete a;
}

void Duplicate(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist,1))
		throw ne;
	int *a = dlist.removeFront();
	int *b = new int;
	*b = *a;
	dlist.insertFront(b);
	dlist.insertFront(a);
}

void Reverse(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist,2))
		throw ne;
	int *a = dlist.removeFront();
	int *b = dlist.removeFront();
	dlist.insertFront(a);
	dlist.insertFront(b);
}

void Print(Dlist<int> &dlist)
{
	NotEnough ne;
	if (!EnoughOperandsCheck(dlist,1))
		throw ne;
	int *a = dlist.removeFront();
	cout << *a << endl;
	dlist.insertFront(a);
}

void Clear(Dlist<int> &dlist)
{
	while (!dlist.isEmpty())
	{
		int *a = dlist.removeFront();
		delete a;
	}
}

void Print_all(Dlist<int> &dlist)
{
	Dlist<int> d1 = dlist;
	while (!d1.isEmpty())
	{
		int *a = d1.removeFront();
		cout << *a << " " ;
		delete a;
	}
	cout << endl;
}

void add_int(string str, Dlist<int> &dlist)
{
	int conv = 0;
	try
	{
		conv = stoi(str);
		if (str.length() != to_string(conv).length())
		{
			BadInput badin;
			throw badin;
		}
		else
		{
			int* a = new int(conv);
			dlist.insertFront(a);
		}

	}
	catch (invalid_argument)
	{
		BadInput badin;
		throw badin;
	}	
}

int main()
{
	Dlist<int> dlist1;
	string str_input;
	while(1)
	{
		cin >> str_input;
		if (str_input == "q")
		{
			Clear(dlist1);
			break;
		}
		else if (str_input == "n")
		{
			try
			{
				Negate(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "d")
		{
			try
			{
				Duplicate(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "r")
		{
			try
			{
				Reverse(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "p")
		{
			try
			{
				Print(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "c")
		{
			Clear(dlist1);
		}
		else if (str_input == "a")
		{
			Print_all(dlist1);
		}
		else if (str_input == "+")
		{
			try
			{
				Plus(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "-")
		{
			try
			{
				Minus(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "*")
		{
			try
			{
				Multiple(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
		}
		else if (str_input == "/")
		{
			try
			{
				Divide(dlist1);
			}
			catch (NotEnough)
			{
				cout << "Not enough operands\n";
			}
			catch (Divide0)
			{
				cout << "Divide by zero\n";
			}
		}
		else
		{
			try
			{
				add_int(str_input, dlist1);
			}
			catch (BadInput)
			{
				cout << "Bad input\n";
			}
		}
	}
	return 0;
}