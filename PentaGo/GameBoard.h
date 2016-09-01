#pragma once

#include "Main_menu.h"

class GameBoard 
{
public:
	int **slots;
	string lastMove = "";

	GameBoard()
	{
		slots = new int*[6];
		for (int i = 0; i < 6; i++)
			slots[i] = new int[6];
		for (int i = 0; i < 6;i++)
		for (int j = 0; j < 6; j++)
			slots[i][j] = 0;
	}

	void printBoard()
	{
		cout << "Current board:\n";
		for (int i = 0; i < 6; i++)
		{
			string lineString = "";
			for (int j = 0; j < 6; j++)
			{
				if (slots[i][j] == 1)
					lineString += "W ";
				else if (slots[i][j] == 2)
					lineString += "B ";
				else
					lineString += "0 ";
				if (j == 2)
					lineString += "| ";
			}
			cout << lineString << endl;
			if (i == 2)
				cout << "-------------\n";
		}
	}

	GameBoard(int *moves[10])
	{
		slots = new int*[6];
		for (int i = 0; i < 6; i++)
			slots[i] = new int[6];
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
				slots[i][j] = moves[i][j];
		}
	}

	void setLastMove(string move)
	{
		lastMove = move;
	}

	void makeMove(int player, int row, int col)
	{
		slots[row - 1][col - 1] = player;
	}

	bool isValidMove(int row, int col)
	{
		return (slots[row - 1][col - 1] == 0);
	}

	void rotateClockwise(int n, int m, int **&mat) {
		int **ret;
		ret = new int*[n];
		for (int i = 0; i < n; i++) ret[i] = new int[m];
		for (int r = 0; r < m; r++) {
			for (int c = 0; c < n; c++) {
				ret[c][m - 1 - r] = mat[r][c];
			}
		}
		for (int i = 0; i < n;i++) 
		for (int j = 0; j < n; j++)
			mat[i][j] = ret[i][j];
	}

	void rotateCounterClockwise(int n,int m, int **&mat) {
		rotateClockwise(n,m,mat);
		rotateClockwise(n,m,mat);
		rotateClockwise(n,m,mat);
	}

	int getUtility()
	{
		int utility = 0;
		int streak = 0;		

		for (int i = 0; i < 6; i++)	
		{
			for (int j = 0; j < 5; j++)	
			{
				if (slots[i][j] == 2 && slots[i][j + 1] == 2)
				{
					utility += streak + 1;
					streak++;
				}
				else
					streak = 0;
			}
		}
		
		for (int i = 0; i < 6; i++)	
		{
			for (int j = 0; j < 5; j++)	
			{
				if (slots[j][i] == 2 && slots[j + 1][i] == 2)
				{
					utility += streak + 1;
					streak++;
				}
				else
					streak = 0;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (slots[i][i] == 2 && slots[i + 1][i + 1] == 2)
			{
				utility += streak + 1;
				streak++;
			}
			else
				streak = 0;
		}

		for (int i = 0; i < 5; i++)
		{
			if (slots[i][5 - i] == 2 && slots[i + 1][4 - i] == 2)
			{
				utility += streak + 1;
				streak++;
			}
			else
				streak = 0;
		}

		return utility;
	}

	vector<GameBoard> getChildren()
	{
		vector<GameBoard> returnList;

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);
					tempBoard.rotateA();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "A");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);
					tempBoard.rotateB();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "B");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);	
					tempBoard.rotateC();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "C");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);	
					tempBoard.rotateD();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "D");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);	
					tempBoard.rotatea();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "a");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);
					tempBoard.rotateb();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "b");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);	
					tempBoard.rotatec();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "c");
					returnList.push_back(tempBoard);
				}
			}
		}

		for (int i = 1; i < 7; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				if (isValidMove(i, j))
				{
					GameBoard tempBoard;
					tempBoard.makeMove(2, i, j);	
					tempBoard.rotated();
					tempBoard.setLastMove(itos(i) + " " + itos(j) + " " + "d");
					returnList.push_back(tempBoard);
				}
			}
		}

		return returnList;
	}

	string getLastMove()
	{
		return lastMove;
	}

	void rotate(string key, int p=-1)
	{
		if (p == -1) return;
		cout << p << ' ' << key << endl;
		if (key[0] >='A' && key[0]<='Z')
		{
			if (key[0]=='A')
			{
				rotateA();
			}
			else if (key[0] == 'B')
			{
				rotateB();
			}
			else if (key[0] == 'C')
			{
				rotateC();
			}
			else if (key[0] == 'D')
			{
				rotateD();
			}
		}
		else	
		{
			if (key[0] == 'a')
			{
				rotatea();
			}
			else if (key[0] == 'b')
			{
				rotateb();
			}
			else if (key[0] == 'c')
			{
				rotatec();
			}
			else if (key[0] == 'd')
			{
				rotated();
			}
		}
	}

	void rotateA()
	{
		int **quadrant;
		
		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3];

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i][j];
			}
		}
		
		rotateCounterClockwise(3,3,quadrant);
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i][j] = quadrant[i][j];
			}
		}
	}

	void rotateB()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3];

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i][j + 3];
			}
		}
		
		rotateCounterClockwise(3,3,quadrant);
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i][j + 3] = quadrant[i][j];
			}
		}
	}

	void rotateC()
	{
		
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3];

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i + 3][j];
			}
		}

		rotateCounterClockwise(3,3,quadrant);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i + 3][j] = quadrant[i][j];
			}
		}
	}

	void rotateD()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3]; 
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i + 3][j + 3];
			}
		}
		
		rotateCounterClockwise(3,3,quadrant);
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i + 3][j + 3] = quadrant[i][j];
			}
		}
	}

	void rotatea()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3];
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i][j];
			}
		}
		
		rotateClockwise(3,3,quadrant);
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i][j] = quadrant[i][j];
			}
		}
	}

	void rotateb()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3]; 
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i][j + 3];
			}
		}
		
		rotateClockwise(3,3,quadrant);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i][j + 3] = quadrant[i][j];
			}
		}
	}

	void rotatec()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3]; 
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i + 3][j];
			}
		}
		
		rotateClockwise(3,3,quadrant);
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i + 3][j] = quadrant[i][j];
			}
		}
	}

	void rotated()
	{
		int **quadrant;

		quadrant = new int*[3];
		for (int i = 0; i < 3; i++) quadrant[i] = new int[3]; 
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				quadrant[i][j] = slots[i + 3][j + 3];
			}
		}
		
		rotateClockwise(3,3,quadrant);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slots[i + 3][j + 3] = quadrant[i][j];
			}
		}
	}

	int determineWinner()
	{
		for (int i = 0; i < 6; i++)
		{
			if (slots[i][0] == 1 && slots[i][1] == 1 && slots[i][2] == 1 && slots[i][3] == 1 && slots[i][4] == 1)
				return 1;
			if (slots[i][0] == 2 && slots[i][1] == 2 && slots[i][2] == 2 && slots[i][3] == 2 && slots[i][4] == 2)
				return 2;
		}

		for (int i = 0; i < 6; i++)
		{
			if (slots[i][1] == 1 && slots[i][2] == 1 && slots[i][3] == 1 && slots[i][4] == 1 && slots[i][5] == 1)
				return 1;
			if (slots[i][1] == 2 && slots[i][2] == 2 && slots[i][3] == 2 && slots[i][4] == 2 && slots[i][5] == 2)
				return 2;
		}

		for (int i = 0; i < 6; i++)
		{
			if (slots[0][i] == 1 && slots[1][i] == 1 && slots[2][i] == 1 && slots[3][i] == 1 && slots[4][i] == 1)
				return 1;
			if (slots[0][i] == 2 && slots[1][i] == 2 && slots[2][i] == 2 && slots[3][i] == 2 && slots[4][i] == 2)
				return 2;
		}

		for (int i = 0; i < 6; i++)
		{
			if (slots[1][i] == 1 && slots[2][i] == 1 && slots[3][i] == 1 && slots[4][i] == 1 && slots[5][i] == 1)
				return 1;
			if (slots[1][i] == 2 && slots[2][i] == 2 && slots[3][i] == 2 && slots[4][i] == 2 && slots[5][i] == 2)
				return 2;
		}
		
		if (slots[0][1] == 1 && slots[1][2] == 1 && slots[2][3] == 1 && slots[3][4] == 1 && slots[4][5] == 1)
			return 1;
		if (slots[0][1] == 2 && slots[1][2] == 2 && slots[2][3] == 2 && slots[3][4] == 2 && slots[4][5] == 2)
			return 2;

		if (slots[1][0] == 1 && slots[2][1] == 1 && slots[3][2] == 1 && slots[4][3] == 1 && slots[5][4] == 1)
			return 1;
		if (slots[1][0] == 2 && slots[2][1] == 2 && slots[3][2] == 2 && slots[4][3] == 2 && slots[5][4] == 2)
			return 2;

		if (slots[0][4] == 1 && slots[1][3] == 1 && slots[2][2] == 1 && slots[3][1] == 1 && slots[4][0] == 1)
			return 1;
		if (slots[0][4] == 2 && slots[1][3] == 2 && slots[2][2] == 2 && slots[3][1] == 2 && slots[4][0] == 2)
			return 2;
		
		if (slots[1][5] == 1 && slots[2][4] == 1 && slots[3][3] == 1 && slots[4][2] == 1 && slots[5][1] == 1)
			return 1;
		if (slots[1][5] == 2 && slots[2][4] == 2 && slots[3][3] == 2 && slots[4][2] == 2 && slots[5][1] == 2)
			return 2;

		if (slots[0][0] == 1 && slots[1][1] == 1 && slots[2][2] == 1 && slots[3][3] == 1 && slots[4][4] == 1)
			return 1;
		if (slots[0][0] == 2 && slots[1][1] == 2 && slots[2][2] == 2 && slots[3][3] == 2 && slots[4][4] == 2)
			return 2;

		if (slots[1][1] == 1 && slots[2][2] == 1 && slots[3][3] == 1 && slots[4][4] == 1 && slots[5][5] == 1)
			return 1;
		if (slots[1][1] == 2 && slots[2][2] == 2 && slots[3][3] == 2 && slots[4][4] == 2 && slots[5][5] == 2)
			return 2;

		if (slots[0][5] == 1 && slots[1][4] == 1 && slots[2][3] == 1 && slots[3][2] == 1 && slots[4][1] == 1)
			return 1;
		if (slots[0][5] == 2 && slots[1][4] == 2 && slots[2][3] == 2 && slots[3][2] == 2 && slots[4][1] == 2)
			return 2;

		if (slots[1][4] == 1 && slots[2][3] == 1 && slots[3][2] == 1 && slots[4][1] == 1 && slots[5][0] == 1)
			return 1;
		if (slots[1][4] == 2 && slots[2][3] == 2 && slots[3][2] == 2 && slots[4][1] == 2 && slots[5][0] == 2)
			return 2;
		return 0;
	}
};