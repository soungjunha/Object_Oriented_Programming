#include "board_widget.h"
#include <QMouseEvent>

// board_widget 생성자(부모 위젯 지정, 내부 Board 8x8로 기본 초기화)
board_widget::board_widget(QWidget *parent)
    : QWidget{parent}, m_board(8)
{
}

// 보드 크기만 바꾸고, 보드 및 착수 가능 위치 초기화
void board_widget::set_board_size(int size)
{
    m_board_size = size;                   // 보드 크기
    m_cell_size = width() / size;          // 한 칸 크기(픽셀) 자동 설정
    m_board.reset(size);                   // Board 클래스도 초기화
    m_is_black_turn = true;                // 흑이 선공
    m_validMoves = m_board.getValidMoves(m_is_black_turn); // 착수 가능 위치
    update();                              // 화면 갱신
}

// 보드 크기와 선공(흑/백) 함께 설정 (게임 불러오기 등)
void board_widget::set_board_size(int size, bool is_black_turn)
{
    m_board_size = size;
    m_cell_size = width() / size;
    m_board.reset(size);
    m_is_black_turn = is_black_turn;       // 턴 정보도 세팅
    m_validMoves = m_board.getValidMoves(m_is_black_turn);
    update();
}

// 보드와 돌 등 실제 UI 그리기 (Qt에서 자동 호출)
void board_widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 안티앨리어싱(부드럽게)

    // 1. 전체 배경
    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    // 2. 격자선 그리기 (가로/세로)
    QVector<QLine> lines;
    for (int i = 1; i < m_board_size; ++i) {
        int pos = i * m_cell_size;
        lines.append(QLine(0, pos, m_board_size * m_cell_size, pos));      // 가로선
        lines.append(QLine(pos, 0, pos, m_board_size * m_cell_size));      // 세로선
    }
    painter.drawLines(lines);

    // 3. 각 칸에 돌/장애물 표시
    for (int i = 0; i < m_board_size; ++i) {
        for (int j = 0; j < m_board_size; ++j) {
            QRect cell_rect(i * m_cell_size, j * m_cell_size, m_cell_size, m_cell_size);
            CellState state = m_board.getCell(i, j);    // 칸 상태 가져옴
            if (state == CellState::Black) {
                painter.setBrush(Qt::black);
                painter.drawEllipse(cell_rect.adjusted(5, 5, -5, -5));   // 흑돌(원)
            }
            else if (state == CellState::White) {
                painter.setBrush(Qt::white);
                painter.drawEllipse(cell_rect.adjusted(5, 5, -5, -5));   // 백돌(원)
            }
            else if (state == CellState::Obstacle) {
                painter.setBrush(Qt::darkBlue);
                painter.drawRect(cell_rect.adjusted(0,0,0,0));           // 장애물(네모)
            }
        }
    }

    // 4. 착수 가능 위치(초록색 사각형) — 리플레이 모드에서는 안 보임
    if (!m_is_replay_mode) {
        painter.setPen(QPen(Qt::green, 3));   // 초록색 테두리
        painter.setBrush(Qt::NoBrush);

        for (const auto& mv : m_validMoves) {
            if (m_board.getCell(mv.first, mv.second) == CellState::Obstacle)
                continue; // 장애물 칸은 건너뜀
            QRect cell_rect(mv.first * m_cell_size, mv.second * m_cell_size, m_cell_size, m_cell_size);
            painter.drawRect(cell_rect.adjusted(5, 5, -5, -5));   // 칸 안쪽에 강조
        }
    }

    // 5. 특정 칸 강조 효과(리플레이, 최근 착수 등)
    if (m_highlight_x >= 0 && m_highlight_y >= 0) {
        painter.setPen(QPen(Qt::red, 4));   // 빨간색 두꺼운 테두리
        QRect cell_rect(m_highlight_x * m_cell_size, m_highlight_y * m_cell_size, m_cell_size, m_cell_size);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(cell_rect.adjusted(6, 6, -6, -6)); // 기존보다 더 안쪽
    }
}

// 마우스 클릭 이벤트 처리 — 오직 게임 모드에서만 착수 처리
void board_widget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x() / m_cell_size; // 클릭 좌표 → 보드 좌표 변환
    int y = event->pos().y() / m_cell_size;

    // 착수 가능 위치가 아니면 무시
    auto it = std::find(m_validMoves.begin(), m_validMoves.end(), std::make_pair(x, y));
    if (it == m_validMoves.end())
        return;

    // 실제 착수+뒤집기 시도 (성공하면...)
    if (m_board.place_stone(x, y, m_is_black_turn)) {
        m_board.save_turn(x, y, m_is_black_turn);            // 턴 이력 저장
        m_is_black_turn = !m_is_black_turn;                  // 턴 교체
        emit turn_changed(m_is_black_turn);                  // 시그널(상태창 등 UI 갱신)
        m_validMoves = m_board.getValidMoves(m_is_black_turn); // 다음 턴 착수 위치

        // 패스 판정 (상대도 둘 수 없으면, 내 턴 → 둘 다 못 두면 게임 끝)
        if (m_validMoves.empty()) {
            emit turn_passed(m_is_black_turn);               // 패스 신호
            m_is_black_turn = !m_is_black_turn;              // 다시 내 턴
            emit turn_changed(m_is_black_turn);
            m_validMoves = m_board.getValidMoves(m_is_black_turn);

            if (m_validMoves.empty()) {
                // 둘 다 착수 불가 → 게임 종료
                int black_count = m_board.count_stone(CellState::Black);
                int white_count = m_board.count_stone(CellState::White);
                QString result;
                if (black_count > white_count)
                    result = "흑돌 승";
                else if (white_count > black_count)
                    result = "백돌 승";
                else
                    result = "무승부";
                emit game_finished(result);   // 게임 종료 신호!
                return;
            }
        }

        update(); // 화면 갱신 (돌/착수 위치/강조 등)
    }
}

// 착수 가능 위치 외부에서 설정 (ex. 리플레이, 수동 UI 갱신 등)
void board_widget::set_valid_moves(const std::vector<std::pair<int, int>>& moves) {
    m_validMoves = moves;
    update();
}
