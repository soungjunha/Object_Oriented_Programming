#include "result_dialog.h"
#include "ui_result_dialog.h"

// 생성자: UI 초기화 및 "확인" 버튼 한글화
result_dialog::result_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::result_dialog)
{
    ui->setupUi(this);

    // QDialogButtonBox의 Ok 버튼 텍스트를 "확인"으로 변경
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("확인");
}

// 소멸자: UI 메모리 해제
result_dialog::~result_dialog()
{
    delete ui;
}

// 결과 텍스트(승, 패, 무승부 등) 라벨에 표시
void result_dialog::set_result_text(const QString& text)
{
    ui->result_label->setText(text);
}
