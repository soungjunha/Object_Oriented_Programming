#include "board_widget.h"

board_widget::board_widget(QWidget *parent)
    : QWidget{parent}
{}

void board_widget::paintEvent(QPaintEvent *event)
{
    QPainter board(this);

    board.setBrush(Qt::white);
    board.drawRect(2,2,width(),height());
}
