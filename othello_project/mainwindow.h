#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>        // 메인 윈도우 프레임워크
#include <QApplication>       // 앱 종료, 전역 이벤트
#include <QDialog>            // 설정/결과 등 모달 대화상자

#include "board.h"            // 오델로 게임 보드 로직

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;             // Qt 디자이너 UI 클래스 선언
}
QT_END_NAMESPACE

// 메인 프로그램 윈도우 클래스 (QMainWindow 상속)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 생성자 (부모 위젯 지정, 기본 nullptr)
    MainWindow(QWidget *parent = nullptr);
    // 소멸자 (동적 할당된 UI 해제)
    ~MainWindow();

    // 리플레이 데이터 저장 (history: 턴별 상태, board_size: 판 크기)
    void set_last_replay(const std::vector<GameTurn>& history, int board_size) {
        m_last_replay_history = history;
        m_last_board_size = board_size;
    }

    // 마지막 게임 리플레이 이력 반환 (읽기 전용)
    const std::vector<GameTurn>& get_last_replay_history() const { return m_last_replay_history; }

    // 마지막 게임 보드 크기 반환
    int get_last_board_size() const { return m_last_board_size; }

    // 진행중 게임 여부 플래그 설정/조회 (이어하기 기능)
    void set_game_in_progress(bool flag) { m_game_in_progress = flag; }
    bool is_game_in_progress() const { return m_game_in_progress; }

private:
    Ui::MainWindow *ui;                     // Qt 디자이너에서 생성된 UI 객체 포인터
    std::vector<GameTurn> m_last_replay_history; // 마지막 게임의 턴별 이력(리플레이용)
    bool m_game_in_progress = false;        // 게임이 진행중인지 여부 (이어하기/버튼 상태)
    int m_last_board_size;                  // 마지막 게임 보드 크기

    // 화면 전환 함수(설정, 게임, 리플레이, 시작)
    void go_to_setting();                   // 설정화면(모달 대화상자)으로 이동
    void go_to_game();                      // 게임화면으로 이동
    void go_to_replay();                    // 리플레이화면으로 이동
    void go_to_start();                     // 시작(메인)화면으로 이동
};

#endif // MAINWINDOW_H
