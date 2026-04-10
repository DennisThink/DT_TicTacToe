
#include "QtTicTacToe_Board.hpp"
#include "SearchEngine.hpp"
#include <QMessageBox>
// 纯图形界面：只负责绘制棋盘和传递点击坐标，不包含任何游戏逻辑
BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 400);
    m_playSide = ChessTypes_T::X_Type;
}

// 设置要绘制的棋盘状态（由外部逻辑调用）
void BoardWidget::updateBoard(const TicTacToeBoard_T& data)
{
    m_board.SetBoard(data);
    update(); // 触发重绘
}

// 重置棋盘显示（清空所有格子）
void BoardWidget::clearBoard()
{
    TicTacToeBoard_T data;
    m_board.SetBoard(data);
    update();
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int cellSize = width() / 3;
    // 绘制网格线
    painter.setPen(QPen(Qt::black, 3));
    for (int i = 1; i < 3; ++i)
    {
        painter.drawLine(i * cellSize, 0, i * cellSize, height());
        painter.drawLine(0, i * cellSize, width(), i * cellSize);
    }

    // 绘制棋子
    QFont font("Arial", cellSize * 0.6, QFont::Bold);
    painter.setFont(font);
    auto data = m_board.GetBoard();
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_WIDTH; y++) {
            if (data._board[x][y] == ChessTypes_T::X_Type) {
                QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
                painter.drawText(rect, Qt::AlignCenter, QString("X"));
            }
            if (data._board[x][y] == ChessTypes_T::O_Type) {
                QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
                painter.drawText(rect, Qt::AlignCenter, QString("O"));
            }
        }
    }
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int cellSize = width() / 3;
        int x = event->pos().x();
        int y = event->pos().y();
        int row = y / cellSize;
        int col = x / cellSize;
        if (row >= 0 && row < 3 && col >= 0 && col < 3)
        {
            {
                GridType_T grid;
                grid._xPos = col;
                grid._yPos = row;
                if (m_board.CanSidePlay(m_playSide, grid))
                {
                    m_board.SidePlay(m_playSide, grid);
                }
            }

            {
                CSearchEngine oEngine;
                GridType_T oMove = oEngine.GetMove(m_board.GetBoard(), ChessTypes_T::O_Type);
                if (m_board.CanSidePlay(ChessTypes_T::O_Type, oMove))
                {
                    m_board.SidePlay(ChessTypes_T::O_Type, oMove);
                }
            }
            {
                if (m_board.IsSideWin(ChessTypes_T::O_Type))
                {
                    QMessageBox::information(this, "TicTacToe", "O side Win。");
                }
                if (m_board.IsSideWin(ChessTypes_T::X_Type))
                {
                    QMessageBox::information(this, "TicTacToe", "X side Win。");
                }
            }
            update();
        }
    }
}

TicTacToeDialog::TicTacToeDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("井字棋 - 图形界面");
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_boardWidget = new BoardWidget(this);
    layout->addWidget(m_boardWidget);

    QPushButton *resetBtn = new QPushButton("重置棋盘", this);
    layout->addWidget(resetBtn, 0, Qt::AlignCenter);

    connect(resetBtn, &QPushButton::clicked, this, &TicTacToeDialog::onResetClicked);

    // 示例：连接点击信号，您应该在这里替换为您自己的逻辑处理函数
}

// 供外部逻辑调用的接口：更新棋盘显示
void TicTacToeDialog::setBoard(const char board[3][3])
{

}

// 清空显示
void TicTacToeDialog::resetDisplay()
{
    m_boardWidget->clearBoard();
}

void TicTacToeDialog::onResetClicked()
{
    // 重置显示，您应该在这里调用您自己的重置逻辑
    m_boardWidget->clearBoard();
    // 例如：您的逻辑 -> resetGameLogic(); 然后 setBoard(您的棋盘数组);
}

void TicTacToeDialog::onCellClicked(int row, int col)
{
    // 在这里调用您自己的落子逻辑
    // 例如：您的逻辑 -> bool valid = yourGame.makeMove(row, col);
    // 然后 if (valid) setBoard(yourGame.getBoard());
    // 之后可以检查游戏是否结束等
    Q_UNUSED(row);
    Q_UNUSED(col);
    // 示例只是弹出一个消息框，实际使用时请删除
    // QMessageBox::information(this, "点击", QString("点击了 (%1, %2)").arg(row).arg(col));
}
