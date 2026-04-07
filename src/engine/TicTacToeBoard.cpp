#include "TicTacToeBoard.h"
#include <iostream>
CTicTacToeBoard::CTicTacToeBoard()
{

}
bool CTicTacToeBoard::IsSideWin(const ChessTypes_T& side) const
{
    bool bWin = true;
    int nCount = 0;
    const auto& data = m_board._board;

    //Horizontal 
    for (int y = 0; y < BOARD_WIDTH; y++)
    {
        nCount = 0;
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (data[x][y] == side)
            {
                nCount++;
            }
        }
        if (nCount == BOARD_WIDTH)
        {
            bWin = true;
            break;
        }
    }
    if (bWin)
    {
        return bWin;
    }

    //Virtical
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        nCount = 0;
        for (int y = 0; y < BOARD_WIDTH; y++) 
        {
            if (data[x][y] == side)
            {
                nCount++;
            }
        }
        if (nCount == BOARD_WIDTH)
        {
            bWin = true;
            break;
        }
    }
    if (bWin)
    {
        return bWin;
    }

    //diagonal
    nCount = 0;
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
       
        if (data[x][x] == side)
        {
            nCount++;
        }
    }
    if (nCount == BOARD_WIDTH)
    {
        bWin = true;
    }
    if (bWin)
    {
        return bWin;
    }

    //diagonal
    nCount = 0;
    for (int x = 0; x < BOARD_WIDTH; x++)
    {

        if (data[x][BOARD_WIDTH-x-1] == side)
        {
            nCount++;
        }
    }
    if (nCount == BOARD_WIDTH)
    {
        bWin = true;
    }
    if (bWin)
    {
        return bWin;
    }
    return false;
}

std::vector<GridType_T> CTicTacToeBoard::GetAllPosibleGrids() const
{
    std::vector<GridType_T> result;
    const auto& data = m_board._board;
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        for (int y = 0; y < BOARD_WIDTH;y++)
        {
            if (data[x][y] == ChessTypes_T::None_Type)
            {
                GridType_T grid;
                grid._xPos = x;
                grid._yPos = y;
                result.push_back(grid);
            }
        }
    }
    return result;
}
bool CTicTacToeBoard::CanSidePlay(const ChessTypes_T& side,const GridType_T& grid) const
{
    if (ChessTypes_T::X_Type == side || ChessTypes_T::O_Type == side)
    {
        if ((0 <= grid._xPos) &&
            (grid._xPos < BOARD_WIDTH))
        {
            if ((0 <= grid._yPos) &&
                (grid._yPos < BOARD_WIDTH))
            {
                if (m_board._board[grid._xPos][grid._yPos] == ChessTypes_T::None_Type) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool CTicTacToeBoard::SidePlay(const ChessTypes_T& side,const GridType_T& grid)
{
    if (CanSidePlay(side, grid))
    {
        m_board._board[grid._xPos][grid._yPos] = side;
    }
    return false;
}

void CTicTacToeBoard::PrintBoard()const
{
    const auto& data = m_board._board;
    std::cout << "--------------------------" << std::endl;
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        for (int y = 0; y < BOARD_WIDTH;y++)
        {
            switch (data[x][y])
            {
            case ChessTypes_T::None_Type:
            {
                std::cout << ".";
            }break;
            case ChessTypes_T::X_Type:
            {
                std::cout << "X";
            }break;
            case ChessTypes_T::O_Type:
            {
                std::cout << "O";
            }break;
            default:
            {

            }break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    return;
}
const TicTacToeBoard_T& CTicTacToeBoard::GetBoard() const
{
    return m_board;
}