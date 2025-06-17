#include "setting_window.h"
#include "ui_setting_window.h"

setting_window::setting_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::setting_window)
{
    ui->setupUi(this);
}

setting_window::~setting_window()
{
    delete ui;
}
