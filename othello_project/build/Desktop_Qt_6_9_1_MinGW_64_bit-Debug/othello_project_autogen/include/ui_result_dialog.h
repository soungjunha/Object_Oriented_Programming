/********************************************************************************
** Form generated from reading UI file 'result_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULT_DIALOG_H
#define UI_RESULT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_result_dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *result_label;

    void setupUi(QDialog *result_dialog)
    {
        if (result_dialog->objectName().isEmpty())
            result_dialog->setObjectName("result_dialog");
        result_dialog->resize(240, 160);
        buttonBox = new QDialogButtonBox(result_dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 120, 221, 41));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Ok);
        result_label = new QLabel(result_dialog);
        result_label->setObjectName("result_label");
        result_label->setGeometry(QRect(55, 50, 130, 40));
        QFont font;
        font.setPointSize(18);
        result_label->setFont(font);

        retranslateUi(result_dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, result_dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, result_dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(result_dialog);
    } // setupUi

    void retranslateUi(QDialog *result_dialog)
    {
        result_dialog->setWindowTitle(QCoreApplication::translate("result_dialog", "Dialog", nullptr));
        result_label->setText(QCoreApplication::translate("result_dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class result_dialog: public Ui_result_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_DIALOG_H
