#ifndef SETTING_WINDOW_H
#define SETTING_WINDOW_H

#include <QWidget>

namespace Ui {
class setting_window;
}

class setting_window : public QWidget
{
    Q_OBJECT

public:
    explicit setting_window(QWidget *parent = nullptr);
    ~setting_window();

private:
    Ui::setting_window *ui;
};

#endif // SETTING_WINDOW_H
