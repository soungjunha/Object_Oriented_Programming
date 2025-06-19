#include "turn_indicator_widget.h"

// 생성자: 부모 위젯 지정(기본 nullptr)
turn_indicator_widget::turn_indicator_widget(QWidget* parent) : QWidget(parent) {}

// 현재 턴(흑/백) 정보 설정 + 화면 갱신 요청
void turn_indicator_widget::setTurn(bool isBlackTurn) {
    m_isBlackTurn = isBlackTurn;
    update();  // paintEvent() 자동 호출
}

// 실제 턴 인디케이터 그리기 (흑/백 원 + 텍스트)
void turn_indicator_widget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);   // 안티앨리어싱
    painter.setPen(Qt::black);

    QRect r(0, 0, width()-1, height()-1); // 전체 위젯 영역
    painter.drawRect(r);                  // 바깥 테두리 네모

    if(m_isBlackTurn) {
        painter.setBrush(Qt::black);                                 // 흑돌
        painter.drawEllipse(r.left()+8, r.top()+8, 30, 30);          // 흑 원
        painter.setPen(Qt::black);
        painter.drawText(r.left()+48, r.top()+28, "흑 턴");           // "흑 턴" 텍스트
    } else {
        painter.setBrush(Qt::white);                                 // 백돌
        painter.drawEllipse(r.left()+8, r.top()+8, 30, 30);          // 백 원
        painter.setPen(Qt::black);
        painter.drawText(r.left()+48, r.top()+28, "백 턴");           // "백 턴" 텍스트
    }
}
