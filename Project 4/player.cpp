#include "player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class HumanPlayer: public Player 
{
//protected:
//	Board *board;
//	Pool *pool;

public:
//	HumanPlayer(Board *board, Pool *pool): board(board), pool(pool){}
	using Player::Player;
	Piece & selectPiece()
	{
		string input;
		bool if_get = false;
		bool if_unused = false;
		while (!(if_get and if_unused))
		{
			cout << "Enter a piece:";
			cin >> input;
			if (input.length() != 4 or
				(input[0] != HCODE[0] and input[0] != HCODE[1]) or (input[1] != CCODE[0] and input[1] != CCODE[1])
				or (input[2] != SCODE[0] and input[2] != SCODE[1]) or (input[3] != TCODE[0] and input[3] != TCODE[1]))
			{
				cout << input << " is an invalid input." << endl;
				continue;
			}
			else
			{
				if_get = true;
				try 
				{
					pool -> getUnusedPiece(input);
				}
				catch (UsedPieceException errPc)
				{
					cout << input << " is already used." << endl;
					continue;
				}
				if_unused = true;
			}
		}
		return (pool -> getUnusedPiece(input));
	}
	Square & selectSquare(const Piece &p)
	{
		string input;
		bool if_get = false;
		bool if_empty = false;
		while (!(if_get and if_empty))
		{
			cout << "Enter a position:";
			cin >> input;
			if (input.length() != 2 or
				input[0] - 'A' < 0 or input[0] - 'A' > 3 or input[1] - '1' < 0 or input[1] - '1' > 3)
			{
				cout << input << "is an invalid input." << endl;
				continue;
			}
			else
			{
				if_get = true;
				try 
				{
					board -> getEmptySquare(input);
				}
				catch (SquareException errsq)
				{
					cout << input << " is  not empty." << endl;
					continue;
				}
				if_empty = true;
			}
		}
		return (board->getEmptySquare(input));
	}

};

static bool bad_judge(Piece p, Board* b1)
{
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			try
			{
				Square sq = b1 -> getEmptySquare(Vaxis(i), Haxis(j));
				if (b1 -> isWinning(p, sq))
					return true;
			}
			catch (SquareException errsq)
			{
				continue;
			}
			
		}
	}
	return false;
}

class MyopicPlayer: public Player 
{
//protected:
//	Board *board;
//	Pool *pool;

public:
	using Player::Player;

	Piece & selectPiece()
	{
		int good_count = 0;
		int good_index[16];
		int unused_count = 0;
		int unused_index[16];
		for (int index = 0; index < 16; index ++)
		{
			try
			{
				Piece p1 = pool -> getUnusedPiece(Height((index & 8)/8), Color((index & 4)/4), Shape((index & 2)/2), Top(index & 1));
				unused_index[unused_count] = index;
				unused_count ++;
				if (bad_judge(p1, board) == false)
				{
					good_index[good_count] = index;
					good_count ++;
				}
			}
			catch (UsedPieceException errPc)
			{
				continue;
			}
			
		}
		if (good_count == 0)
		{
			int rand_index = unused_index[rand() % unused_count];
			return pool -> getUnusedPiece(Height((rand_index & 8)/8), Color((rand_index & 4)/4), Shape((rand_index & 2)/2), Top(rand_index & 1));
		}
		else
		{
			int rand_index = good_index[rand() % good_count];
			return pool -> getUnusedPiece(Height((rand_index & 8)/8), Color((rand_index & 4)/4), Shape((rand_index & 2)/2), Top(rand_index & 1));
		}
	}

	Square & selectSquare(const Piece &p)
	{
		int empty_count = 0;
		int empty_index[16];
		for (int i = 0; i < 4; i ++)
		{
			for (int j = 0; j < 4; j ++)
			{
				try
				{
					Square sq1 = board -> getEmptySquare(Vaxis(i), Haxis(j));
					empty_index[empty_count] = 10*i + j;
					empty_count ++;
					if (board -> isWinning(p, sq1))
						return board -> getEmptySquare(Vaxis(i), Haxis(j));
				}
				catch (SquareException errsq)
				{
					continue;
				}
			}
		}
		int index = rand() % empty_count;
		return board -> getEmptySquare(Vaxis((empty_index[index] - empty_index[index] %10) /10), Haxis(empty_index[index] %10));
	}
};

//static HumanPlayer HP;
//static MyopicPlayer MP;

extern Player *getHumanPlayer(Board *b, Pool *p)
{
	return (Player *) new HumanPlayer(b, p);
}

extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s)
{
	srand(s);
	return (Player *) new MyopicPlayer(b, p);
}

