#include "piece.h"
using namespace std;

Piece::Piece(Height h, Color c, Shape s, Top t): h(h), c(c), s(s), t(t), used(false) {}

bool Piece::compareHeight(const Piece &p) const
{
	if (h == p.h)
		return true;
	else
		return false;
}

bool Piece::compareColor(const Piece &p) const
{
	if (c == p.c)
		return true;
	else
		return false;
}

bool Piece::compareShape(const Piece &p) const
{
	if (s == p.s)
		return true;
	else
		return false;
}

bool Piece::compareTop(const Piece &p) const
{
	if (t == p.t)
		return true;
	else
		return false;
}

bool Piece::isUsed() const
{
	return used;
}

void Piece::setUsed(bool u)
{
	used = u;
}

string Piece::toString() const
{
	string s1 = "";
	s1 = s1 + HCODE[h] + CCODE[c] + SCODE[s] + TCODE[t];
	return s1;
}