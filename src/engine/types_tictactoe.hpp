#ifndef _TYPES_TIC_TAC_TOE_H_
#define _TYPES_TIC_TAC_TOE_H_
const static int BOARD_WIDTH=3;
enum class ChessTypes_T
{
    None_Type=-1,
    X_Type=0,
    O_Type=1,
};

struct GridType_T
{
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
    ChessTypes_T _board[BOARD_WIDTH][BOARD_WIDTH];
};
#endif