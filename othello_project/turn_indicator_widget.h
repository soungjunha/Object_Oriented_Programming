#ifndef TURN_INDICATOR_WIDGET_H
#define TURN_INDICATOR_WIDGET_H

#include <QWidget>      // Qt 위젯 기본 클래스
#include <QPainter>     // 직접 그리기(QPainter 사용)

class turn_indicator_widget : public QWidget {
    Q_OBJECT
public:
    // 생성자(부모 위젯 지정, 기본값 nullptr)
    explicit turn_indicator_widget(QWidget* parent = nullptr);

    // 현재 턴(흑: true, 백: false) 설정 함수
    void setTurn(bool isBlackTurn);

protected:
    // 위젯 직접 그리기(턴에 따라 원, 텍스트 등 색상/이미지 표현)
    void paintEvent(QPaintEvent* event) override;

private:
    bool m_isBlackTurn = true;  // 현재 턴: 흑(true), 백(false)
};

#endif // TURN_INDICATOR_WIDGET_H
