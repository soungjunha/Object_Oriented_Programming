#include "setting_dialog.h"
#include "ui_setting_dialog.h"

setting_dialog::setting_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::setting_dialog)
{
    ui->setupUi(this);

    ui->board_size_label->setNum(6);
    ui->obstacle_num_label->setNum(0);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("확인");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("취소");

}

setting_dialog::~setting_dialog()
{
    delete ui;
}

void setting_dialog::on_board_size_valueChanged(int value)
{
    if (value % 2 != 0){
        value--;
        ui->board_size->setValue(value);
    }
    ui->board_size_label->setNum(value);
    board_size=value;
}


void setting_dialog::on_obstacle_num_valueChanged(int value)
{
    ui->obstacle_num_label->setNum(value);
    obstacle_count=value;
}


void setting_dialog::on_black_player_clicked()
{
    turn_player=0;
}

void setting_dialog::on_white_player_clicked()
{
    turn_player=1;
}
