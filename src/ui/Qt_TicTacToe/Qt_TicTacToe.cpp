// main.cpp

#include "QtTicTacToe_Board.hpp"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TicTacToeDialog dialog;
    dialog.show();
    return app.exec();
}