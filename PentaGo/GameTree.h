#pragma once

#include "Main_menu.h"
#include "GameBoard.h"

class GameTree {
public:
	GameBoard thisBoard;
	vector <GameTree> children;

	GameTree(GameBoard board)
	{
		thisBoard = board;
	}

	void populateNodeChildren()
	{
		vector<GameBoard> boardChildren = thisBoard.getChildren();
		children.clear();
		for (int i = 0; i < boardChildren.size(); i++)
		{
			children.push_back(GameTree(boardChildren[i]));
		}
	}

	int childNumber()
	{
		return children.size();
	}

	vector <GameTree> getChildTrees()
	{
		return children;
	}

	GameBoard getBoard()
	{
		return thisBoard;
	}
};
