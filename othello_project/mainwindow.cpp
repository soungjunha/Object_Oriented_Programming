#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->page_3,&start::go_to_setting,this,&MainWindow::go_to_setting);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go_to_setting(){
    ui->stackedWidget->setCurrentIndex(2);
}
