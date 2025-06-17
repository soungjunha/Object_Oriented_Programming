#ifndef REPLAY_WINDOW_H
#define REPLAY_WINDOW_H

#include <QWidget>

namespace Ui {
class replay_window;
}

class replay_window : public QWidget
{
    Q_OBJECT

public:
    explicit replay_window(QWidget *parent = nullptr);
    ~replay_window();

private slots:
    void on_go_to_start_clicked();

private:
    Ui::replay_window *ui;

signals:
    void go_to_start();
};

#endif // REPLAY_WINDOW_H
