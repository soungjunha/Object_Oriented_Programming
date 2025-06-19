#ifndef RESULT_DIALOG_H
#define RESULT_DIALOG_H

#include <QDialog>          // 모달 대화상자 기본 클래스
#include <QPushButton>      // 확인/취소 버튼 등 (필요 시)

namespace Ui {
class result_dialog;        // Qt 디자이너 UI 클래스 선언
}

// 오델로 결과(승패/무승부) 출력용 대화상자 클래스
class result_dialog : public QDialog
{
    Q_OBJECT

public:
    // 생성자(부모 위젯 지정, 기본값 nullptr)
    explicit result_dialog(QWidget *parent = nullptr);

    // 소멸자(UI 메모리 해제)
    ~result_dialog();

    // 결과 문자열(예: "흑 승!", "무승부" 등) 표시용 함수
    void set_result_text(const QString& text);

private:
    Ui::result_dialog *ui;  // Qt 디자이너에서 생성된 UI 포인터
};

#endif // RESULT_DIALOG_H
