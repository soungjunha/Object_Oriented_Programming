#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class setting_dialog;
}

class setting_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit setting_dialog(QWidget *parent = nullptr);
    ~setting_dialog();

    int board_size;       // 보드 크기
    int obstacle_count;   // 장애물 개수
    bool turn_player;     // 0: 흑, 1: 백

private slots:

    void on_board_size_valueChanged(int value);

    void on_obstacle_num_valueChanged(int value);

    void on_black_player_clicked();

    void on_white_player_clicked();

private:
    Ui::setting_dialog *ui;
};

#endif // SETTING_DIALOG_H
