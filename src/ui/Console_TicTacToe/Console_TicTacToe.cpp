#include <iostream>
#include "TicTacToeBoard.h"
#include "SearchEngine.hpp"
int main(int argc,char * argv[])
{
    std::cout<<"this is a console_tic-tac-toe program"<<std::endl;
    CTicTacToeBoard board;
    board.PrintBoard();
    std::cout << "-----------------------------------" << std::endl;
    CSearchEngine engine;
    engine.GetMove(board.GetBoard(), ChessTypes_T::X_Type);
    std::cout << "-----------------------------------" << std::endl;
    return 0;
}