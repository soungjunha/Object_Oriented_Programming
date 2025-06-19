#ifndef REPLAY_WINDOW_H
#define REPLAY_WINDOW_H

#include <QWidget>             // Qt 위젯 기반
#include "board_widget.h"      // 오델로 보드 렌더링 위젯
#include <QPainter>            // 커스텀 그리기용
#include <QMessageBox>         // 메시지 박스(에러/알림 등)
#include "mainwindow.h"        // 메인윈도우와 연동

namespace Ui {
class replay_window;           // Qt 디자이너 UI 클래스 선언
}

class MainWindow;              // MainWindow 전방 선언(포인터용)

// 게임 리플레이 전용 화면(위젯)
class replay_window : public QWidget
{
    Q_OBJECT

public:
    // 생성자(부모 위젯 지정, 기본값 nullptr)
    explicit replay_window(QWidget *parent = nullptr);

    // 소멸자(UI 해제)
    ~replay_window();

    // 리플레이용 턴 이력, 보드 크기 등 데이터 전달(초기화)
    // history: 턴별 상태, board_size: 판 크기
    void set_replay_data(const std::vector<GameTurn>& history, int board_size);

private slots:
    // "메인화면" 버튼 클릭 시 (메인화면 복귀)
    void on_go_to_start_clicked();

    // 이전 턴(Prev) 버튼 클릭 시 (한 턴 앞으로)
    void on_prev_clicked();

    // 다음 턴(Next) 버튼 클릭 시 (한 턴 뒤로)
    void on_next_clicked();

    // 슬라이더/스핀박스 등에서 턴 값 바뀔 때 호출
    void on_turn_valueChanged(int value);

private:
    Ui::replay_window *ui;            // Qt UI 포인터
    std::vector<GameTurn> m_history;  // 리플레이용 턴별 상태 이력
    int m_board_size = 8;             // 보드 크기
    int m_current_turn = 0;           // 현재 보여주는 턴(0번부터)
    MainWindow* m_mainwindow = nullptr; // 메인윈도우 포인터(화면 전환용)
    int total_black = 0;              // 흑돌 개수(현재 턴 기준)
    int total_white = 0;              // 백돌 개수(현재 턴 기준)

    // 현재 턴의 보드 상태를 보드 위젯에 반영 및 갱신
    void update_board();

signals:
    // 메인화면 복귀 요청 시그널
    void go_to_start();
};

#endif // REPLAY_WINDOW_H
