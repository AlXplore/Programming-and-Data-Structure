#include <iostream>
#include <cstdlib>
#include "piece.h"
#include "quarto.h"
#include "pool.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "exceptions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string firstPlayer = argv[1];
	string secondPlayer = argv[2];
	int sequence[2];
	int seq_index = 0;
	int seed = 1;
	if (argc < 4)
		seed = 1;
	else
		seed = atoi(argv[3]);
	if (firstPlayer[0] == 'h')
		sequence[0] = 0;
	else if (firstPlayer[0] == 'm')
		sequence[0] = 1;
	if (secondPlayer[0] == 'h')
		sequence[1] = 0;
	else if (secondPlayer[0] == 'm')
		sequence[1] = 1;

	Board board1;
	Pool pool1;
	Player *players[2];
//	Player *player2;
	if (sequence[0] == 0)
		players[0] = getHumanPlayer(&board1, &pool1);
	else if (sequence[0] == 1)
		players[0] = getMyopicPlayer(&board1, &pool1, seed);
	if (sequence[1] == 0)
		players[1] = getHumanPlayer(&board1, &pool1);
	else if (sequence[1] == 1)
		players[1] = getMyopicPlayer(&board1, &pool1, seed);

	bool is_winning = false;
	cout << board1.toString() << endl;
	cout << pool1.toString() << endl;
	while (!is_winning)
	{
		cout << "Player " << seq_index + 1 << "'s turn to select a piece:" << endl;
		Piece piece_select = players[seq_index] -> selectPiece();
//		piece_select.setUsed(true);
		string piece_select_str = piece_select.toString();
		cout << piece_select_str << " selected.\n" << endl;

		if (seq_index == 0)
			seq_index ++;
		else if (seq_index == 1)
			seq_index --;
		cout << "Player " << seq_index + 1 << "'s turn to select a square:" << endl;
		Square square_select = players[seq_index] -> selectSquare(pool1.getUnusedPiece(piece_select_str));
		string square_select_str = square_select.toString();

		board1.place(pool1.getUnusedPiece(piece_select_str), board1.getEmptySquare(square_select_str));
		cout << square_select_str << " selected.\n" << endl;
		cout << board1.toString() << endl;
		cout << pool1.toString() << endl;
		is_winning = board1.isWinning(piece_select, square_select);
		if (is_winning)
		{
			cout << "Player " << seq_index +1 << " has won!" << endl;
			break;
		}
		if (pool1.toString() == "")
		{
			cout << "It is a draw." << endl;
			break;
		}
	}
	return 0;
}