#ifndef START_H
#define START_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();

private slots:
    void on_new_game_clicked();

    void on_continue_game_clicked();

    void on_replay_clicked();

    void on_quit_clicked();

    void on_load_game_clicked();

private:
    Ui::start *ui;

signals:
    void change_setting_dialog();
    void change_game_window();
    void change_replay_window();
    void quit();
};

#endif // START_H
