#include <iostream>
#include "TicTacToeBoard.h"
#include "SearchEngine.hpp"
#include "SearchEngineConsole.hpp"
int TwoComputePlay(int argc,char * argv[])
{
    std::cout<<"this is a console_tic-tac-toe program"<<std::endl;
    CTicTacToeBoard board;
    board.PrintBoard();
    std::cout << "-----------------------------------" << std::endl;
    ChessTypes_T xSide = ChessTypes_T::X_Type;
    ChessTypes_T oSide = ChessTypes_T::O_Type;
    GridType_T xMove;
    GridType_T oMove;
    bool xWin = board.IsSideWin(xSide);
    bool oWin = board.IsSideWin(oSide);
    while ((!xWin) && (!oWin))
    {
        {
            CSearchEngine xEngine;
            xMove = xEngine.GetMove(board.GetBoard(), ChessTypes_T::X_Type);
            if (board.CanSidePlay(xSide, xMove))
            {
                board.SidePlay(xSide, xMove);
            }
            else
            {
                break;
            }
        }
        board.PrintBoard();
        {
            CSearchEngine oEngine;
            oMove = oEngine.GetMove(board.GetBoard(), ChessTypes_T::O_Type);
            if (board.CanSidePlay(oSide, oMove))
            {
                board.SidePlay(oSide, oMove);
            }
            else
            {
                break;
            }
        }
        board.PrintBoard();
        xWin = board.IsSideWin(xSide);
        oWin = board.IsSideWin(oSide);
    }

    std::cout << "xWin: " << xWin << "  oWin: " << oWin << std::endl;
    board.PrintBoard();
    std::cout << "-----------------------------------" << std::endl;
    int x = 0;
    std::cin >> x;

    return 0;
}

int main(int argc, char* argv[])
{
    std::cout << "this is a console_tic-tac-toe program" << std::endl;
    CTicTacToeBoard board;
    board.PrintBoard();
    std::cout << "-----------------------------------" << std::endl;
    ChessTypes_T xSide = ChessTypes_T::X_Type;
    ChessTypes_T oSide = ChessTypes_T::O_Type;
    GridType_T xMove;
    GridType_T oMove;
    bool xWin = board.IsSideWin(xSide);
    bool oWin = board.IsSideWin(oSide);
    while ((!xWin) && (!oWin))
    {
        {
            SearchEngineConsole xEngine;
            xMove = xEngine.GetMove(board.GetBoard(), ChessTypes_T::X_Type);
            if (board.CanSidePlay(xSide, xMove))
            {
                board.SidePlay(xSide, xMove);
            }
            else
            {
                break;
            }
        }
        board.PrintBoard();
        {
            CSearchEngine oEngine;
            oMove = oEngine.GetMove(board.GetBoard(), ChessTypes_T::O_Type);
            if (board.CanSidePlay(oSide, oMove))
            {
                board.SidePlay(oSide, oMove);
            }
            else
            {
                break;
            }
        }
        board.PrintBoard();
        xWin = board.IsSideWin(xSide);
        oWin = board.IsSideWin(oSide);
    }

    std::cout << "xWin: " << xWin << "  oWin: " << oWin << std::endl;
    board.PrintBoard();
    std::cout << "-----------------------------------" << std::endl;
    int x = 0;
    std::cin >> x;

    return 0;
}