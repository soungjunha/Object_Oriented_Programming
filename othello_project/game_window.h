#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QWidget>
#include <QMessageBox>             // 메시지 박스(게임 종료 등) 사용

#include "result_dialog.h"         // 결과 창(승패/무승부)
#include "board.h"                 // 오델로 보드 로직
#include "mainwindow.h"            // 메인윈도우와 연동

namespace Ui { class game_window; } // Qt UI 폼 클래스 선언

class MainWindow;                  // MainWindow 클래스(포워드 선언)

class game_window : public QWidget // 오델로 게임 진행 화면(위젯)
{
    Q_OBJECT

public:
    // 생성자(부모 위젯 지정, 기본 nullptr)
    game_window(QWidget* parent = nullptr);

    // MainWindow 포인터 포함 생성자(메인윈도우와 직접 연결)
    explicit game_window(MainWindow* mainwindow, QWidget *parent);

    // 소멸자(동적 할당된 UI 해제)
    ~game_window();

    // 보드/장애물/선공 등 설정값 반영 (게임 시작 시 호출)
    void set_config(int board_size, int obstacle_count, bool turn_player);

    // 현재 턴(흑/백) 강제 지정
    void set_current_turn(bool isBlackTurn);

    // 메인윈도우 포인터 저장(메뉴 복귀 등 연동)
    void set_mainwindow(MainWindow* mw) { m_mainwindow = mw; }

protected:
    // paintEvent 오버라이드 (필요 시 화면 직접 그리기)
    void paintEvent(QPaintEvent* event) override;

private slots:
    // "메인화면" 버튼 클릭 시 호출(메인화면 이동)
    void on_go_to_start_clicked();

    // 게임 종료 시 호출(승패결과 처리/다이얼로그 출력)
    void on_game_finished(const QString& result);

    // 턴 패스 발생 시 호출(알림/상태 갱신 등)
    void on_turn_passed(bool is_black_turn);

    // Undo 버튼 클릭 시(되돌리기 기능)
    void on_undo_clicked();

private:
    Ui::game_window *ui;           // UI 객체(디자이너 연결)
    bool m_isBlackTurn = true;     // 현재 턴(흑 true, 백 false)
    MainWindow* m_mainwindow = nullptr; // 메인윈도우 포인터(화면 전환용)
    int total_turn = 0;            // 전체 진행된 턴 수
    int total_black = 0;           // 흑돌 개수
    int total_white = 0;           // 백돌 개수

signals:
    // 메인화면으로 돌아가야 할 때 발생(메인윈도우에 알림)
    void go_to_start();
};

#endif
