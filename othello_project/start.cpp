#include "start.h"
#include "ui_start.h"

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
    emit go_to_setting();
}

