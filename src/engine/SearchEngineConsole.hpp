#ifndef _SEARCH_ENGINE_CONSOLE_HPP_
#define _SEARCH_ENGINE_CONSOLE_HPP_
#include "SearchEngineBase.hpp"
class SearchEngineConsole:public SearchEngineBase
{
public:
	SearchEngineConsole();
	virtual GridType_T GetMove(const TicTacToeBoard_T& board, const ChessTypes_T side) override;
};
#endif