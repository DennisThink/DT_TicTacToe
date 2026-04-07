#ifndef _TIC_TAC_TOE_BOARD_H_
#define _TIC_TAC_TOE_BOARD_H_
#include "types_tictactoe.hpp"
#include <vector>
class CTicTacToeBoard
{
public:
    CTicTacToeBoard();
    bool IsSideWin(const ChessTypes_T& side) const;
    std::vector<GridType_T> GetAllPosibleGrids() const;
    bool CanSidePlay(const ChessTypes_T& side,const GridType_T& grid) const;
    bool SidePlay(const ChessTypes_T& side,const GridType_T& grid);
    void PrintBoard()const;
    const TicTacToeBoard_T& GetBoard() const;
private:
    TicTacToeBoard_T m_board;
};
#endif