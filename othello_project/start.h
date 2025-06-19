#ifndef START_H
#define START_H

#include <QWidget>         // Qt 위젯 기본 클래스
#include <QDialog>         // (필요시, 설정창 등)

namespace Ui {
class start;               // Qt 디자이너 UI 클래스 선언
}

// 오델로 메인(시작) 화면 위젯 클래스
class start : public QWidget
{
    Q_OBJECT

public:
    // 생성자(부모 위젯 지정, 기본값 nullptr)
    explicit start(QWidget *parent = nullptr);

    // 소멸자(UI 메모리 해제)
    ~start();

private slots:
    // "새 게임 시작" 버튼 클릭 시 호출 (설정창 이동)
    void on_new_game_clicked();

    // "이어하기" 버튼 클릭 시 호출 (진행중 게임 복귀)
    void on_continue_game_clicked();

    // "리플레이" 버튼 클릭 시 호출 (리플레이 화면 이동)
    void on_replay_clicked();

    // "종료" 버튼 클릭 시 호출 (프로그램 종료)
    void on_quit_clicked();

    // "불러오기" 버튼 클릭 시 호출 (저장된 게임 불러오기)
    void on_load_game_clicked();

private:
    Ui::start *ui;         // Qt 디자이너에서 생성된 UI 포인터

signals:
    // 설정창(게임 설정)으로 이동 요청 시그널
    void change_setting_dialog();

    // 게임진행 화면으로 이동 요청 시그널
    void change_game_window();

    // 리플레이 화면으로 이동 요청 시그널
    void change_replay_window();

    // 프로그램 종료 요청 시그널
    void quit();
};

#endif // START_H
