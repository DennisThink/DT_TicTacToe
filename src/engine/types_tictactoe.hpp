#ifndef _TYPES_TIC_TAC_TOE_H_
#define _TYPES_TIC_TAC_TOE_H_
#include <string>
const static int BOARD_WIDTH=3;
enum class ChessTypes_T
{
    None_Type=-1,
    X_Type=0,
    O_Type=1,
};

struct GridType_T
{
    GridType_T() {
        _xPos = 0;
        _yPos = 0;
    }
    int _xPos;
    int _yPos;
};

struct TicTacToeBoard_T
{
    TicTacToeBoard_T() {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_WIDTH; y++) {
                _board[x][y] = ChessTypes_T::None_Type;
            }
        }
    }

    bool operator ==(const TicTacToeBoard_T& other) const {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_WIDTH; y++) {
                if (_board[x][y] != other._board[x][y]) {
                    return false;
                }
            }
        }
        return true;
    }
    ChessTypes_T _board[BOARD_WIDTH][BOARD_WIDTH];
};
std::string ToString(const ChessTypes_T& side);
#endif