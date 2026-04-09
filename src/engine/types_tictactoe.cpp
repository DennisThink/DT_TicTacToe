#include "types_tictactoe.hpp"
std::string ToString(const ChessTypes_T& side)
{
    switch (side)
    {
    case ChessTypes_T::X_Type:
    {
        return "X";
    }break;
    case ChessTypes_T::O_Type:
    {
        return "O";
    }break;
    default:
    {
        return ".";
    }break;
    }
    return ".";
}