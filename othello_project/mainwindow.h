#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();\

private:
    Ui::MainWindow *ui;
    void go_to_setting();
    void go_to_game();
    void go_to_replay();
    void go_to_start();
};
#endif // MAINWINDOW_H
