/********************************************************************************
** Form generated from reading UI file 'setting_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_WINDOW_H
#define UI_SETTING_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting_window
{
public:
    QLabel *label;

    void setupUi(QWidget *setting_window)
    {
        if (setting_window->objectName().isEmpty())
            setting_window->setObjectName("setting_window");
        setting_window->resize(200, 300);
        label = new QLabel(setting_window);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 100, 101, 101));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        retranslateUi(setting_window);

        QMetaObject::connectSlotsByName(setting_window);
    } // setupUi

    void retranslateUi(QWidget *setting_window)
    {
        setting_window->setWindowTitle(QCoreApplication::translate("setting_window", "Form", nullptr));
        label->setText(QCoreApplication::translate("setting_window", "50", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting_window: public Ui_setting_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_WINDOW_H
