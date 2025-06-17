#include "replay_window.h"
#include "ui_replay_window.h"

replay_window::replay_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::replay_window)
{
    ui->setupUi(this);
}

replay_window::~replay_window()
{
    delete ui;
}

void replay_window::on_go_to_start_clicked()
{
    emit go_to_start();
}

