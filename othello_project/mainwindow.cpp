#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "setting_dialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->page,&start::change_setting_dialog,this,&MainWindow::go_to_setting);
    connect(ui->page,&start::change_game_window,this,&MainWindow::go_to_game);
    connect(ui->page,&start::change_replay_window,this,&MainWindow::go_to_replay);
    connect(ui->page,&start::quit,qApp,&QApplication::quit);

    connect(ui->page_2,&game_window::go_to_start,this,&MainWindow::go_to_start);

    connect(ui->page_4,&replay_window::go_to_start,this,&MainWindow::go_to_start);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go_to_setting(){
    // 1. 설정 다이얼로그 띄우기
    setting_dialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        // 2. 설정값 받아오기
        int board_size = dialog.board_size;
        int obstacle_count = dialog.obstacle_count;
        bool turn_player = dialog.turn_player;

        // 3. game_window 페이지를 가져옴 (Object Inspector 기준 page_2)
        game_window *gw = qobject_cast<game_window*>(ui->stackedWidget->widget(1));

        // 4. game_window에 값 전달
        gw->set_config(board_size, obstacle_count, turn_player);

        // 5. 게임 페이지로 전환
        ui->stackedWidget->setCurrentIndex(1); // 1번 인덱스가 game_window
    }
    // 취소면 아무 일도 안 함
}

void MainWindow::go_to_game(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::go_to_replay(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::go_to_start(){
    ui->stackedWidget->setCurrentIndex(0);
}
