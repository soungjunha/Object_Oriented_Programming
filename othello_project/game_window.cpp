#include "game_window.h"
#include "ui_game_window.h"
#include <QPainter>

// 기본 생성자: UI 설정 및 board_widget과 신호 연결
game_window::game_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game_window)
{
    ui->setupUi(this);

    // board_widget의 턴 변경 신호와 연동 (상태창 및 턴 인디케이터 동기화)
    connect(ui->board, &board_widget::turn_changed, this, &game_window::set_current_turn);
    connect(ui->board, &board_widget::turn_changed,ui->turn_indicator, &turn_indicator_widget::setTurn);
    connect(ui->board, &board_widget::game_finished, this, &game_window::on_game_finished);
    connect(ui->board, &board_widget::turn_passed, this, &game_window::on_turn_passed);
}

// MainWindow 포인터 포함 생성자 (메뉴복귀 등 메인윈도우와 연동)
game_window::game_window(MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game_window), m_mainwindow(mainwindow)
{
    ui->setupUi(this);

    // board_widget의 신호들 동일하게 연결
    connect(ui->board, &board_widget::turn_changed, this, &game_window::set_current_turn);
    connect(ui->board, &board_widget::turn_changed,ui->turn_indicator, &turn_indicator_widget::setTurn);
    connect(ui->board, &board_widget::game_finished, this, &game_window::on_game_finished);
    connect(ui->board, &board_widget::turn_passed, this, &game_window::on_turn_passed);
}

// 소멸자: UI 메모리 해제
game_window::~game_window()
{
    delete ui;
}

// 게임 설정값(보드 크기/장애물/선공) 반영 (새 게임 시작 시)
void game_window::set_config(int board_size, int obstacle_count, bool turn_player)
{
    ui->board->set_board_size(board_size, turn_player);   // (1) 보드 크기+선공 설정
    ui->board->get_board().place_obstacles(obstacle_count); // (2) 장애물 배치
    ui->board->get_board().save_init_state(turn_player);    // (3) 초기 상태 이력 저장
    ui->board->update();                                   // 보드 위젯 강제 갱신
    set_current_turn(turn_player);                         // 상태창/턴 인디케이터 동기화
}

// 현재 턴(흑/백) 상태 동기화 및 repaint
void game_window::set_current_turn(bool isBlackTurn) {
    m_isBlackTurn = isBlackTurn;
    update();  // paintEvent() 호출 → 턴 표시/점수 등 자동 갱신
}

// paintEvent: 상태창(현재 턴, 점수 등) 직접 그리기 + UI 라벨 갱신
void game_window::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    // 우측 상단에 턴 표시 영역
    QRect turnRect(width()-150, 20, 120, 50);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(turnRect);

    if(m_isBlackTurn) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(turnRect.left()+10, turnRect.top()+10, 30, 30); // 흑돌 원
        painter.setPen(Qt::black);
        painter.drawText(turnRect.left()+50, turnRect.top()+32, "흑 턴");    // 텍스트
    } else {
        painter.setBrush(Qt::white);
        painter.drawEllipse(turnRect.left()+10, turnRect.top()+10, 30, 30); // 백돌 원
        painter.setPen(Qt::black);
        painter.drawText(turnRect.left()+50, turnRect.top()+32, "백 턴");    // 텍스트
    }

    // 현재 턴/점수/턴 수 UI 라벨 업데이트
    total_turn = ui->board->get_board().get_history().size(); // 전체 턴 수
    total_black = ui->board->get_board().count_stone(CellState::Black); // 흑돌 개수
    total_white = ui->board->get_board().count_stone(CellState::White); // 백돌 개수
    QString current_turn_str = m_isBlackTurn ? "흑" : "백";

    ui->total_turn->setText(QString("전체턴: %1턴(%2)").arg(total_turn).arg(current_turn_str));
    ui->total_black->setText(QString("흑돌: %1").arg(total_black));
    ui->total_white->setText(QString("백돌: %1").arg(total_white));
}

// "메인화면" 버튼 클릭 시 호출: 메인윈도우로 복귀 요청
void game_window::on_go_to_start_clicked()
{
    emit go_to_start();
}

// 게임 종료(흑/백/무승부) 시 호출: 결과 다이얼로그+리플레이 저장 여부 처리
void game_window::on_game_finished(const QString& result) {
    result_dialog dialog(this);
    dialog.set_result_text(result);
    dialog.exec(); // 결과 안내 다이얼로그(모달)

    // 리플레이 저장 여부 묻기(Yes/No)
    if(QMessageBox::question(this, "리플레이 저장", "리플레이를 저장하시겠습니까?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        if (m_mainwindow)
            m_mainwindow->set_last_replay(ui->board->get_board().get_history(),
                                          ui->board->get_board().size());
        QMessageBox::information(this, "저장 완료", "리플레이가 저장되었습니다.");
    }
    if(m_mainwindow) m_mainwindow->set_game_in_progress(false); // 진행중 게임 플래그 해제
    emit go_to_start(); // 메인화면으로 복귀
}

// 턴 패스(착수 불가) 시 호출: 정보 메시지 출력
void game_window::on_turn_passed(bool is_black_turn) {
    QString msg = is_black_turn ?
                      "흑돌 플레이어는 둘 곳이 없어 턴이 스킵됩니다." :
                      "백돌 플레이어는 둘 곳이 없어 턴이 스킵됩니다.";
    QMessageBox::information(this, "턴 스킵", msg);
}

// board_widget의 보드 상태 강제 동기화 (리플레이 등)
void board_widget::set_board_state(const std::vector<std::vector<CellState>>& state) {
    // state(2차원 벡터) 크기와 현재 보드 크기가 다르면 크기도 맞춤
    int new_size = state.size();
    if (new_size != m_board_size) {
        set_board_size(new_size);
    }
    m_board.set_board_state(state); // 내부 Board 객체 상태 동기화
    update(); // 화면 갱신
}

// Undo(되돌리기) 버튼 클릭 시: 두 턴 전 상태로 복구, 점수/턴/착수 위치 동기화
void game_window::on_undo_clicked()
{
    ui->board->get_board().undo(); // board.cpp의 undo() 호출

    // 상태 복원: 이력의 마지막(두 턴 전)의 정보로 UI 갱신
    const auto& prev = ui->board->get_board().get_history().back();
    //m_isBlackTurn = prev.is_black_turn; // (공격권 동기화 필요시 사용)
    total_black   = prev.total_black;
    total_white   = prev.total_white;
    total_turn    = (int)ui->board->get_board().get_history().size() - 1;

    // 착수 가능 위치도 복원
    ui->board->set_valid_moves(
        ui->board->get_board().getValidMoves(m_isBlackTurn)
        );

    // UI 전체 갱신(보드/상태창)
    ui->board->update();
    update();
}
