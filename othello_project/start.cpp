#include "start.h"
#include "ui_start.h"
#include "setting_dialog.h"

start::start(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}

void start::on_new_game_clicked()
{
    emit change_setting_dialog();
}

void start::on_continue_game_clicked()
{
    emit change_game_window();
}

void start::on_replay_clicked()
{
    emit change_replay_window();
}


void start::on_quit_clicked()
{
    emit quit();
}



void start::on_load_game_clicked()
{
    emit change_game_window();
}

