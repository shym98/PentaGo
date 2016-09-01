#pragma once

#include "GameBoard.h"
#include "GameTree.h"
#include "AI.h"

class Main {
public:
	int depth = 2;

	GameBoard board;
	int currentPlayer = 0;

	void parseInput(string input)
	{
		cout << input << endl;
		input += " ";
		string array[3], t ="";
		int k = 0;
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == ' ')
				array[k++] = t, t = "";
			else
			t += input[i];
		}
		if (board.isValidMove(ftoi(array[0]), ftoi(array[1])))
			{
				if (currentPlayer==2) board.makeMove(currentPlayer, ftoi(array[0]), ftoi(array[1]));
				if (currentPlayer == 1)
					currentPlayer = 2;
				else
					currentPlayer = 1;
				if (board.determineWinner() == 0 && currentPlayer==2)
					board.rotate(array[2]);
				else if (board.determineWinner() == 1)
					cout<<"Human wins.";
				else
					cout<<"AI wins!";
			}

	}

	void main()
	{
		board = GameBoard();
		currentPlayer = 1;
	}
};
