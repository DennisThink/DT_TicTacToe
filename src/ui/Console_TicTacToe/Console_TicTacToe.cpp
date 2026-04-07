#include <iostream>
#include "TicTacToeBoard.h"
int main(int argc,char * argv[])
{
    std::cout<<"this is a console_tic-tac-toe program"<<std::endl;
    CTicTacToeBoard board;
    board.PrintBoard();
    return 0;
}