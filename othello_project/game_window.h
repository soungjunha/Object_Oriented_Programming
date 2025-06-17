#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QWidget>

namespace Ui {
class game_window;
}

class game_window : public QWidget
{
    Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window();

    void set_config(int board_size, int obstacle_count, bool turn_player);

private slots:
    void on_go_to_start_clicked();

private:
    Ui::game_window *ui;

signals:
    void go_to_start();

};

#endif // GAME_WINDOW_H
