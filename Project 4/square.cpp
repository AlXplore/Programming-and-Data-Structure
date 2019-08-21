#include "square.h"
#include "exceptions.h"
using namespace std;

Square::Square(Vaxis v, Haxis h): v(v), h(h), p(NULL) {}

Vaxis Square::getV() const
{
	return v;
}

void Square::setV(Vaxis v)
{
	this -> v = v;
}

Haxis Square::getH() const
{
	return h;
}

void Square::setH(Haxis h)
{
	this -> h = h;
}

const Piece & Square::getPiece() const
{
	if (p != NULL)
		return *p;
	else
	{
		SquareException errSq(*this, "empty");
		throw errSq;
	}
}

void Square::setPiece(const Piece *p)
{
	this -> p = p;
}

bool Square::isEmpty() const
{
	if (p == NULL)
		return true;
	else
		return false;
}

bool Square::isOnFirstDiagonal() const
{
	if (int(v) == int(h))
		return true;
	else
		return false;
}

bool Square::isOnSecondDiagonal() const
{
	if ((v + h) == 3)
		return true;
	else
		return false;
}

string Square::toString() const
{
	string s1 = "  ";
	char v_char = char('A'+v);
	char h_char = char('1'+h);
	s1[0] = v_char;
	s1[1] = h_char;
	return s1;
}