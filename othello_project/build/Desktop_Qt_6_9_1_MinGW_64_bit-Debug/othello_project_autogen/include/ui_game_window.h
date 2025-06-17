/********************************************************************************
** Form generated from reading UI file 'game_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_WINDOW_H
#define UI_GAME_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_window
{
public:
    QLabel *label;

    void setupUi(QWidget *game_window)
    {
        if (game_window->objectName().isEmpty())
            game_window->setObjectName("game_window");
        game_window->resize(1200, 675);
        label = new QLabel(game_window);
        label->setObjectName("label");
        label->setGeometry(QRect(850, 70, 171, 121));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);

        retranslateUi(game_window);

        QMetaObject::connectSlotsByName(game_window);
    } // setupUi

    void retranslateUi(QWidget *game_window)
    {
        game_window->setWindowTitle(QCoreApplication::translate("game_window", "Form", nullptr));
        label->setText(QCoreApplication::translate("game_window", "game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_window: public Ui_game_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_WINDOW_H
