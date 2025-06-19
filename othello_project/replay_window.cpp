#include "replay_window.h"
#include "ui_replay_window.h"

// 생성자: UI 세팅 및 버튼 신호 연결
replay_window::replay_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::replay_window)
{
    ui->setupUi(this);

    // 이전/다음 턴 버튼 클릭 신호 슬롯 연결
    connect(ui->prev_turn, &QPushButton::clicked, this, &replay_window::on_prev_clicked);
    connect(ui->next_turn, &QPushButton::clicked, this, &replay_window::on_next_clicked);
}

// 소멸자: UI 메모리 해제
replay_window::~replay_window()
{
    delete ui;
}

// 리플레이 데이터 세팅(이력, 보드크기), 초기화 및 슬라이더 설정
void replay_window::set_replay_data(const std::vector<GameTurn>& history, int board_size)
{
    m_history = history;               // 턴별 상태 저장
    m_board_size = board_size;         // 보드 크기
    m_current_turn = 0;                // 항상 0번 턴(시작 상태)부터
    ui->board->set_replay_mode(true);  // 리플레이 모드 ON(착수 위치 표시 안함)
    ui->turn->setMinimum(0);           // 슬라이더 최소값
    ui->turn->setMaximum(m_history.empty() ? 0 : (m_history.size()-1)); // 최대 턴
    ui->turn->setValue(0);             // 현재 슬라이더 값도 0으로
    update_board();                    // 보드/점수/라벨 등 모두 갱신
}

// 현재 턴(m_current_turn)에 맞춰 보드/강조/라벨 갱신
void replay_window::update_board()
{
    if (m_history.empty()) return; // 리플레이 데이터 없음

    // 현재 턴의 보드 상태 UI에 반영
    ui->board->set_board_state(m_history[m_current_turn].board_snapshot);

    // 슬라이더 값도 현재 턴과 동기화(드래그 시에도 호출됨)
    ui->turn->setValue(m_current_turn);

    // [착수 위치 강조] 최근 턴에서 착수 좌표 있으면 강조(없으면 -1,-1로 해제)
    int hx = m_history[m_current_turn].x;
    int hy = m_history[m_current_turn].y;
    if (hx >= 0 && hy >= 0) {
        ui->board->set_highlight_pos(hx, hy);
    } else {
        ui->board->set_highlight_pos(-1, -1);
    }

    // 턴/플레이어 정보 라벨 갱신 ("전체턴: x / n턴 (흑/백)")
    QString info = QString("전체턴: %1 / %2턴  (%3)")
                       .arg(m_current_turn)
                       .arg(m_history.size())
                       .arg(m_history[m_current_turn].is_black_turn ? "흑" : "백");
    ui->total_turn->setText(info);

    // 돌 개수 라벨 갱신
    total_black = ui->board->get_board().count_stone(CellState::Black);
    total_white = ui->board->get_board().count_stone(CellState::White);

    ui->total_black->setText(QString("흑돌: %1").arg(total_black));
    ui->total_white->setText(QString("백돌: %1").arg(total_white));
}

// "메인화면" 버튼 클릭 시 호출: 메인화면 복귀 신호 emit
void replay_window::on_go_to_start_clicked()
{
    emit go_to_start();
}

// "이전 턴" 버튼 클릭 시: 턴 감소, 보드 갱신
void replay_window::on_prev_clicked()
{
    if(m_current_turn > 0) {
        m_current_turn--;
        update_board();
    }
}

// "다음 턴" 버튼 클릭 시: 턴 증가, 보드 갱신
void replay_window::on_next_clicked()
{
    if(m_current_turn < (int)m_history.size() - 1) {
        m_current_turn++;
        update_board();
    }
}

// 슬라이더/스핀박스 값 바뀔 때: 현재 턴 갱신 및 보드 갱신
void replay_window::on_turn_valueChanged(int value)
{
    m_current_turn = value;
    update_board();
}
