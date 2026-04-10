#include "SearchEngineConsole.hpp"
#include <iostream>
#include "TicTacToeBoard.h"
SearchEngineConsole::SearchEngineConsole()
{

}

GridType_T SearchEngineConsole::GetMove(const TicTacToeBoard_T& board, const ChessTypes_T side)
{
	{
		GridType_T result;
		CTicTacToeBoard consoleBoard;
		consoleBoard.SetBoard(board);
		auto allPos = consoleBoard.GetAllPosibleGrids();
		int posIndex = 0;
		std::cout << "Posible Position: " << std::endl;
		for (auto posItem : allPos)
		{
			{
				posIndex++;
				if (posIndex % BOARD_WIDTH == 0)
				{
					std::cout << std::endl;
				}
			}
			std::cout << "(" << posItem._xPos << "," << posItem._yPos << ")" << "    ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Please input your choice:" << std::endl;
		std::cout << "input X pos:";
		std::cin >> result._xPos;
		std::cout << "Input y pos";
		std::cin >> result._yPos;
		//
		for (auto posItem : allPos)
		{
			if (posItem._xPos == result._xPos && posItem._yPos == result._yPos)
			{
				return result;
			}
		}
	}
	{
		GridType_T result;
		return result;
	}
}