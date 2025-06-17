#include "game_window.h"
#include "ui_game_window.h"

game_window::game_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game_window)
{
    ui->setupUi(this);
}

game_window::~game_window()
{
    delete ui;
}

void game_window::set_config(int board_size, int obstacle_count, bool turn_player)
{
    // 각종 설정값을 멤버변수에 저장
    ui->size->setNum(board_size);
    ui->ob->setNum(obstacle_count);
    ui->fr->setText((turn_player)?"백":"흑");
    // 게임 초기화 등 추가 작업

}

void game_window::on_go_to_start_clicked()
{
    emit go_to_start();
}
