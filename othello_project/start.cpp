#include "start.h"
#include "ui_start.h"
#include "setting_dialog.h"

// 생성자: UI 초기화
start::start(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
}

// 소멸자: UI 메모리 해제
start::~start()
{
    delete ui;
}

// [새 게임 시작] 버튼 클릭 시: 설정창(모달)으로 전환 요청
void start::on_new_game_clicked()
{
    emit change_setting_dialog();
}

// [이어하기] 버튼 클릭 시: 게임화면(진행중 게임 복귀) 전환 요청
void start::on_continue_game_clicked()
{
    emit change_game_window();
}

// [리플레이] 버튼 클릭 시: 리플레이 화면 전환 요청
void start::on_replay_clicked()
{
    emit change_replay_window();
}

// [종료] 버튼 클릭 시: 프로그램 종료 요청
void start::on_quit_clicked()
{
    emit quit();
}

// [불러오기] 버튼 클릭 시: (저장된 게임 복구, 기본은 이어하기와 동일 동작)
void start::on_load_game_clicked()
{
    emit change_game_window();
}
