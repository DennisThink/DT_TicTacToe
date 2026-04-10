#ifndef _QT_TIC_TAC_TOE_BOARD_H_
#define _QT_TIC_TAC_TOE_BOARD_H_
#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "TicTacToeBoard.h"
// 纯图形界面：只负责绘制棋盘和传递点击坐标，不包含任何游戏逻辑
class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent = nullptr);
    // 设置要绘制的棋盘状态（由外部逻辑调用）
    void updateBoard(const TicTacToeBoard_T& data);
    void clearBoard();

signals:
    // 当用户点击某个格子时发出信号，参数为行和列（0-2）
    void cellClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
private:
    CTicTacToeBoard m_board;
    ChessTypes_T m_playSide;
};

// 示例对话框，展示如何将 BoardWidget 与您自己的逻辑结合
class TicTacToeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TicTacToeDialog(QWidget* parent = nullptr);
  

    // 供外部逻辑调用的接口：更新棋盘显示
    void setBoard(const char board[3][3]);
 

    // 清空显示
    void resetDisplay();

private slots:
    void onResetClicked();

    void onCellClicked(int row, int col);

private:
    CTicTacToeBoard m_board;
    BoardWidget* m_boardWidget;
};
#endif