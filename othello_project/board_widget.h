#ifndef BOARD_WIDGET_H
#define BOARD_WIDGET_H

#include <QWidget>
#include <QPainter>

class board_widget : public QWidget
{
    Q_OBJECT
public:
    explicit board_widget(QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // BOARD_WIDGET_H
