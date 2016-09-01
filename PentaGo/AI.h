#pragma once

#include "Main_menu.h"
#include "GameTree.h"
#include <ctime>

class AI {
public:
	GameBoard maxBoard;	
	int max = 0;		
	int depth = 0;

	AI(int d)
	{
		depth = d;
		max = 0;
	}

	GameBoard getBoard()
	{
		return maxBoard;
	}

	//int start = clock() / CLOCKS_PER_SEC;

	int intelligentMove(int depth, GameTree currentTree, bool maximizingPlayer)
	{
		int bestVal = 0;
		
		/*int f = clock() / CLOCKS_PER_SEC;
		if (f - start > 20) return bestVal;*/

		if (depth == 0)
		{
			return currentTree.getBoard().getUtility();
		}

		if (maximizingPlayer)
		{
			bestVal = -1000000000;
			currentTree.populateNodeChildren();
			vector<GameTree> childTrees = currentTree.getChildTrees();
			
			for (int i = 0; i < childTrees.size(); i++)
			{
				int thisVal = intelligentMove(depth - 1, childTrees[i], false);
				/*int q = clock() / CLOCKS_PER_SEC;
				if (q - start > 20) return bestVal;*/
				if (bestVal < thisVal)
					bestVal = thisVal;
			}

			if (bestVal >= max)
			{
				max = bestVal;
				maxBoard = currentTree.getBoard();
			}
			return bestVal;
		}
		else
		{
			bestVal = 1000000000;
			currentTree.populateNodeChildren();
			vector <GameTree> childTrees = currentTree.getChildTrees();
			for (int i = 0; i < childTrees.size(); i++)
			{
				int thisVal = intelligentMove(depth - 1, childTrees[i], true);
				/*int q = clock() / CLOCKS_PER_SEC;
				if (q - start > 20) return bestVal;*/
				if (bestVal > thisVal)
					bestVal = thisVal;
			}
			return bestVal;
		}
	}
};