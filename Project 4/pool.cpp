#include "pool.h"
#include "exceptions.h"
using namespace std;
Pool::Pool()
{
	Piece p1(SHORT, BEIGE, CIRCLE, HOLLOW);
	Piece p2(SHORT, BEIGE, CIRCLE, SOLID);
	Piece p3(SHORT, BEIGE, SQUARE, HOLLOW);
	Piece p4(SHORT, BEIGE, SQUARE, SOLID);
	Piece p5(SHORT, SEPIA, CIRCLE, HOLLOW);
	Piece p6(SHORT, SEPIA, CIRCLE, SOLID);
	Piece p7(SHORT, SEPIA, SQUARE, HOLLOW);
	Piece p8(SHORT, SEPIA, SQUARE, SOLID);
	Piece p9(TALL,  BEIGE, CIRCLE, HOLLOW);
	Piece p10(TALL, BEIGE, CIRCLE, SOLID);
	Piece p11(TALL, BEIGE, SQUARE, HOLLOW);
	Piece p12(TALL, BEIGE, SQUARE, SOLID);
	Piece p13(TALL, SEPIA, CIRCLE, HOLLOW);
	Piece p14(TALL, SEPIA, CIRCLE, SOLID);
	Piece p15(TALL, SEPIA, SQUARE, HOLLOW);
	Piece p16(TALL, SEPIA, SQUARE, SOLID);
	pieces[0] = p1;
	pieces[1] = p2;
	pieces[2] = p3;
	pieces[3] = p4;
	pieces[4] = p5;
	pieces[5] = p6;
	pieces[6] = p7;
	pieces[7] = p8;
	pieces[8] = p9;
	pieces[9] = p10;
	pieces[10] = p11;
	pieces[11] = p12;
	pieces[12] = p13;
	pieces[13] = p14;
	pieces[14] = p15;
	pieces[15] = p16;
}
Piece & Pool::getUnusedPiece(int index)
{
	if (pieces[index].isUsed() == true)
	{
		UsedPieceException errPc(pieces[index]);
		throw errPc;
	}
	else
		return pieces[index];
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t)
{
	int index = 8*int(h) + 4*int(c) + 2*int(s) + int(t);
	return getUnusedPiece(index);
}

Piece & Pool::getUnusedPiece(const std::string &in)
{
	int index = 0;
	if (in[0] == 'T')
		index += 8;
	if (in[1] == 'E')
		index += 4;
	if (in[2] == 'Q')
		index += 2;
	if (in[3] == 'O')
		index += 1;
	return getUnusedPiece(index);
}

string Pool::toString() const
{
	string s1 = "Available:\n";
	string s0 = "";
	for (int i = 0; i < 16; i ++)
	{
		if (pieces[i].isUsed() == false)
			s1 = s1 + pieces[i].toString()[0] + pieces[i].toString()[1] + " ";
	}
	s1 = s1 + "\n";
	for (int i = 0; i < 16; i ++)
	{
		if (pieces[i].isUsed() == false)
			s1 = s1 + pieces[i].toString()[2] + pieces[i].toString()[3] + " ";
	}
	s1 = s1 + "\n";
	if (s1 == "Available:\n\n\n")
		return s0;
	else
		return s1;
}
