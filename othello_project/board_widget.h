#ifndef BOARD_WIDGET_H
#define BOARD_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "board.h"

// 오델로 보드 위젯 클래스 선언 (QWidget을 상속받음)
class board_widget : public QWidget
{
    Q_OBJECT
public:
    // 생성자: 부모 위젯 지정(기본값 nullptr)
    explicit board_widget(QWidget *parent = nullptr);

    // 보드 크기만 변경 (게임 재시작/초기화 시)
    void set_board_size(int size);

    // 보드 크기, 선공(흑/백) 설정
    void set_board_size(int size, bool is_black_turn);

    // 현재 턴(흑 true, 백 false) 반환
    bool get_current_turn() const { return m_is_black_turn; }

    // 보드(Board) 객체 참조 반환 (읽기/쓰기용)
    Board& get_board() { return m_board; }

    // 보드(Board) 객체 상수 참조 반환 (읽기 전용)
    const Board& get_board() const { return m_board; }

    // 외부에서 보드 상태 직접 설정
    void set_board_state(const std::vector<std::vector<CellState>>& state);

    // (리플레이 등) 특정 칸 강조 효과 좌표 설정
    void set_highlight_pos(int x, int y) { m_highlight_x = x; m_highlight_y = y; update(); }

    // 리플레이 모드 전환 (true: 리플레이, false: 일반)
    void set_replay_mode(bool is_replay) { m_is_replay_mode = is_replay; update(); }

    // 현재 리플레이 모드 여부 반환
    bool is_replay_mode() const { return m_is_replay_mode; }

    // 착수 가능 위치 목록 설정 (UI에 표시용)
    void set_valid_moves(const std::vector<std::pair<int, int>>& moves);

signals:
    // 턴이 변경될 때 신호 발생 (게임윈도우 UI 갱신용)
    void turn_changed(bool is_black_turn);

    // 게임이 끝났을 때 신호 발생 (결과창 호출용)
    void game_finished(const QString& result);

    // 턴 패스 발생 시 신호 (패스 알림/로직처리용)
    void turn_passed(bool skipped_player); // true: 흑, false: 백

protected:
    // 보드 위젯 그리기 이벤트 (보드/돌/장애물 등 UI 렌더링)
    void paintEvent(QPaintEvent *event) override;

    // 마우스 클릭 이벤트 (착수, 리플레이 이동 등 처리)
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_board_size = 8;                       // 현재 보드 크기 (ex: 8)
    float m_cell_size = 50;                     // 한 칸 크기(픽셀, UI용)
    Board m_board;                              // 오델로 게임 보드(로직 포함)
    bool m_is_black_turn = true;                // 현재 턴: 흑(true), 백(false)
    std::vector<std::pair<int,int>> m_validMoves; // 착수 가능 위치(리스트)
    int m_highlight_x = -1, m_highlight_y = -1; // 강조 칸 좌표 (-1,-1: 강조X)
    bool m_is_replay_mode = false;              // 리플레이 모드 여부 (기본 false)
};

#endif
