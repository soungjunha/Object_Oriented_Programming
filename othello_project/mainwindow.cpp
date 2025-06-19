#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "setting_dialog.h"

// MainWindow 생성자: UI 초기화 및 각 화면 간 신호 연결
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                       // UI 세팅(디자이너 폼 불러오기)
    ui->stackedWidget->setCurrentIndex(0);   // 시작화면(메인)으로 설정

    // start(메인화면)의 신호들을 MainWindow의 슬롯에 연결 (화면 전환)
    connect(ui->page,&start::change_setting_dialog,this,&MainWindow::go_to_setting);
    connect(ui->page,&start::change_game_window,this,&MainWindow::go_to_game);
    connect(ui->page,&start::change_replay_window,this,&MainWindow::go_to_replay);
    connect(ui->page,&start::quit,qApp,&QApplication::quit);

    // 게임창에서 "메인화면" 버튼 누르면 시작화면 복귀
    connect(ui->page_2,&game_window::go_to_start,this,&MainWindow::go_to_start);

    // 리플레이창에서 "메인화면" 버튼 누르면 시작화면 복귀
    connect(ui->page_4,&replay_window::go_to_start,this,&MainWindow::go_to_start);

    // 게임윈도우에 MainWindow 포인터 전달(리플레이 저장 등 위해)
    game_window *gw = qobject_cast<game_window*>(ui->stackedWidget->widget(1));
    if (gw) gw->set_mainwindow(this);
}

// MainWindow 소멸자: UI 메모리 해제
MainWindow::~MainWindow()
{
    delete ui;
}

// [설정화면]으로 이동: QDialog로 설정값 받고, 게임 초기화 후 게임창으로 전환
void MainWindow::go_to_setting(){
    setting_dialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) { // "확인" 클릭시만
        int board_size = dialog.board_size;
        int obstacle_count = dialog.obstacle_count;
        bool turn_player = dialog.turn_player;

        // 게임윈도우에 설정값 전달 및 초기화
        game_window *gw = qobject_cast<game_window*>(ui->stackedWidget->widget(1));
        gw->set_config(board_size, obstacle_count, turn_player);

        m_game_in_progress = true; // 새 게임 시작하면 이어하기 가능 플래그 true

        ui->stackedWidget->setCurrentIndex(1); // 1번: 게임화면으로 전환
    }
    // 취소(QDialog::Rejected)이면 아무 동작도 안 함
}

// [이어하기] 버튼: 게임 진행중이면 게임화면, 아니면 경고 메시지
void MainWindow::go_to_game() {
    // 이어할 게임 없으면 경고
    if (!m_game_in_progress) {
        QMessageBox::warning(this, "이어하기 불가", "진행중인 게임이 없습니다.");
        return;
    }
    ui->stackedWidget->setCurrentIndex(1); // 1번 인덱스: 게임화면
}

// [리플레이] 버튼: 리플레이 데이터 있으면 리플레이화면, 아니면 경고 메시지
void MainWindow::go_to_replay(){
    if (m_last_replay_history.empty()) {
        QMessageBox::warning(this, "리플레이 없음", "저장된 리플레이가 없습니다.");
        return;
    }
    replay_window* rw = qobject_cast<replay_window*>(ui->stackedWidget->widget(3));
    rw->set_replay_data(m_last_replay_history, m_last_board_size); // 데이터 전달
    ui->stackedWidget->setCurrentIndex(3); // 3번 인덱스: 리플레이화면
}

// [메인화면]으로 전환 (게임 진행중 플래그는 유지)
void MainWindow::go_to_start(){
    //m_game_in_progress = false; // 메인 복귀 시 플래그를 굳이 끄지 않음 (게임 중단시만 off)
    ui->stackedWidget->setCurrentIndex(0); // 0번 인덱스: 메인화면(시작화면)
}
