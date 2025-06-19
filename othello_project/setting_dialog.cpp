#include "setting_dialog.h"
#include "ui_setting_dialog.h"

// 생성자: UI 초기값 세팅 및 버튼 한글화
setting_dialog::setting_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::setting_dialog),board_size(6),obstacle_count(0),turn_player(1)
{
    ui->setupUi(this);

    ui->board_size_label->setNum(6); // 초기 라벨도 6으로

    // 확인/취소 버튼 한글로 변경
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("확인");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("취소");
}

// 소멸자: UI 메모리 해제
setting_dialog::~setting_dialog()
{
    delete ui;
}

// [슬라이더/스핀박스 등] 보드 크기 변경 시 호출
void setting_dialog::on_board_size_valueChanged(int value)
{
    if (value % 2 != 0){
        value--;                        // 홀수면 짝수로 조정(1 빼기)
        ui->board_size->setValue(value);// UI에도 반영
    }
    ui->board_size_label->setNum(value); // 라벨에 표시
    board_size = value;                  // 변수에도 저장
}

// [스핀박스 등] 장애물 개수 값 바뀔 때 (즉시)
void setting_dialog::on_obstacle_num_valueChanged(int arg1)
{
    obstacle_count = arg1;
}

// [장애물 입력박스 포커스 아웃 등] 입력 확정 시, 범위/짝수 자동 보정
void setting_dialog::on_obstacle_num_editingFinished()
{
    int val = ui->obstacle_num->text().toInt();

    // 0~16 범위 보정
    if (val < 0) val = 0;
    else if (val > 16) val = 16;

    // 짝수 보정(홀수면 -1)
    if (val % 2 == 1) val -= 1;

    // 최종 값 반영 (UI+변수 모두)
    obstacle_count = val;
    ui->obstacle_num->setValue(val);
}

// [흑 선공] 버튼 클릭 시
void setting_dialog::on_black_player_clicked()
{
    turn_player = 1;
}

// [백 선공] 버튼 클릭 시
void setting_dialog::on_white_player_clicked()
{
    turn_player = 0;
}

// [랜덤 선공] 버튼 클릭 시 (0 또는 1 무작위)
void setting_dialog::on_random_clicked()
{
    turn_player = QRandomGenerator::global()->bounded(2);
}
