#include "board.h"
#include "exceptions.h"
using namespace std;

Board::Board()
{
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			grid[i][j].setV(Vaxis(i));
			grid[i][j].setH(Haxis(j));
		}
	}
}

Square & Board::getSquare(Vaxis v, Haxis h)
{
	return grid[v][h];
}

Square & Board::getEmptySquare(Vaxis v, Haxis h)
{
	if (!grid[v][h].isEmpty())
	{
		SquareException errSq(grid[v][h], "empty");
		throw errSq;
	}
	else
		return grid[v][h];
}

Square & Board::getEmptySquare(const std::string &s)
{
	return getEmptySquare(Vaxis(s[0] - 'A'), Haxis(s[1] - '1'));
}

void Board::place(Piece &p, Square &sq)
{
	p.setUsed(true);
	int v = int(sq.getV());
	int h = int(sq.getH());
	grid[v][h].setPiece(&p);
//	sq.setPiece(&p);
}

bool Board::isWinning(const Piece &p, const Square &sq)
{
	int change_back = 0;
	int sq_v = sq.getV();
	int sq_h = sq.getH();
	if (grid[sq_v][sq_h].isEmpty())
	{
		grid[sq_v][sq_h].setPiece(&p);
		change_back = 1;
	}
	bool win_flag = false;
	for (int prop = 0; prop < 4; prop ++)
	{
		//check the rows
		for (int row = 0; row < 4; row ++)
		{
			if (grid[row][0].isEmpty() or grid[row][1].isEmpty() or grid[row][2].isEmpty() or grid[row][3].isEmpty())
				continue;
			if (grid[row][0].getPiece().toString()[prop] == grid[row][1].getPiece().toString()[prop] 
					and grid[row][0].getPiece().toString()[prop] == grid[row][2].getPiece().toString()[prop]
					and grid[row][0].getPiece().toString()[prop] == grid[row][3].getPiece().toString()[prop])
			{
				win_flag = true;
				break;
			}
		}
		if (win_flag)
			break;
		//check the columns
		for (int col = 0; col < 4; col ++)
		{
			if (grid[0][col].isEmpty() or grid[1][col].isEmpty() or grid[2][col].isEmpty() or grid[3][col].isEmpty())
				continue;
			if (grid[0][col].getPiece().toString()[prop] == grid[1][col].getPiece().toString()[prop]
					and grid[0][col].getPiece().toString()[prop] == grid[2][col].getPiece().toString()[prop]
					and grid[0][col].getPiece().toString()[prop] == grid[3][col].getPiece().toString()[prop])
			{
				win_flag = true;
				break;
			}
		}
		if (win_flag)
			break;
		//check the diags
		if (!(grid[0][0].isEmpty() or grid[1][1].isEmpty() or grid[2][2].isEmpty() or grid[3][3].isEmpty()))
		{
			if (grid[0][0].getPiece().toString()[prop] == grid[1][1].getPiece().toString()[prop]
					and grid[0][0].getPiece().toString()[prop] == grid[2][2].getPiece().toString()[prop]
					and grid[0][0].getPiece().toString()[prop] == grid[3][3].getPiece().toString()[prop])
			{
				win_flag = true;
				break;
			}
		}
		
		if (!(grid[0][3].isEmpty() or grid[1][2].isEmpty() or grid[2][1].isEmpty() or grid[3][0].isEmpty()))
		{
			if (grid[0][3].getPiece().toString()[prop] == grid[1][2].getPiece().toString()[prop]
					and grid[0][3].getPiece().toString()[prop] == grid[2][1].getPiece().toString()[prop]
					and grid[0][3].getPiece().toString()[prop] == grid[3][0].getPiece().toString()[prop])
			{
				win_flag = true;
				break;
			}		
		}
		
	}
	if (change_back)
	{
		grid[sq_v][sq_h].setPiece(NULL);
	}
	return win_flag;
}


string Board::toString() const
{
	string s1[4][2];
	string s0, s_line, s_out;
	s1[0][0] = " a |";
	s1[0][1] = "   |";
	s1[1][0] = " b |";
	s1[1][1] = "   |";
	s1[2][0] = " c |";
	s1[2][1] = "   |";
	s1[3][0] = " d |";
	s1[3][1] = "   |";
	s0 = "     1    2    3    4\n";
	s_line = "   +----+----+----+----+\n";

	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			if (!grid[i][j].isEmpty())
			{
				s1[i][0] += " " + grid[i][j].getPiece().toString().substr(0,2) + " |";
				s1[i][1] += " " + grid[i][j].getPiece().toString().substr(2,2) + " |";
			}
			else
			{
				s1[i][0] += "    |";
				s1[i][1] += "    |";
			}
		}
		s1[i][0] += "\n";
		s1[i][1] += "\n";
	}
	s_out = s0 + s_line;
	for (int i = 0; i < 4; i ++)
		s_out = s_out + s1[i][0] + s1[i][1] + s_line;
	return s_out;
}
