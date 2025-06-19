#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>            // 모달 설정 대화상자 기본 클래스
#include <QPushButton>        // 확인/취소 등 버튼
#include <QRandomGenerator>   // 랜덤(선공 랜덤 선택 등) 기능

namespace Ui {
class setting_dialog;         // Qt 디자이너 UI 클래스 선언
}

// 오델로 게임 설정(보드 크기, 장애물, 선공)용 대화상자 클래스
class setting_dialog : public QDialog
{
    Q_OBJECT

public:
    // 생성자(부모 위젯 지정, 기본 nullptr)
    explicit setting_dialog(QWidget *parent = nullptr);

    // 소멸자(UI 메모리 해제)
    ~setting_dialog();

    int board_size;         // 보드 크기(6~12, 짝수)
    int obstacle_count;     // 장애물 개수(0~16)
    bool turn_player;       // 선공(흑:1, 백:0, 랜덤은 코드에서 변환)

private slots:
    // 보드 크기 스핀박스/슬라이더 값 변경 시 호출
    void on_board_size_valueChanged(int value);

    //void on_obstacle_num_valueChanged(int value); // (미사용, 주석처리됨)

    // "흑 선공" 버튼 클릭 시 호출
    void on_black_player_clicked();

    // "백 선공" 버튼 클릭 시 호출
    void on_white_player_clicked();

    // "랜덤 선공" 버튼 클릭 시 호출
    void on_random_clicked();

    // 장애물 개수 값 변경 시 호출
    void on_obstacle_num_valueChanged(int arg1);

    // 장애물 입력 박스 입력 완료 시 호출
    void on_obstacle_num_editingFinished();

private:
    Ui::setting_dialog *ui; // Qt 디자이너에서 생성된 UI 포인터
};

#endif // SETTING_DIALOG_H
