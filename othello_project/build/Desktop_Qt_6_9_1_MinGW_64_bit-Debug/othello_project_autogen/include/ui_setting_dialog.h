/********************************************************************************
** Form generated from reading UI file 'setting_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_DIALOG_H
#define UI_SETTING_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting_dialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSlider *board_size;
    QLabel *board_size_label;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *obstacle_num;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *black_player;
    QRadioButton *white_player;
    QRadioButton *random;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *setting_dialog)
    {
        if (setting_dialog->objectName().isEmpty())
            setting_dialog->setObjectName("setting_dialog");
        setting_dialog->resize(240, 320);
        QFont font;
        font.setPointSize(10);
        setting_dialog->setFont(font);
        verticalLayoutWidget = new QWidget(setting_dialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 241, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        board_size = new QSlider(verticalLayoutWidget);
        board_size->setObjectName("board_size");
        board_size->setMinimum(6);
        board_size->setMaximum(12);
        board_size->setSingleStep(2);
        board_size->setPageStep(2);
        board_size->setTracking(true);
        board_size->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(board_size);

        board_size_label = new QLabel(verticalLayoutWidget);
        board_size_label->setObjectName("board_size_label");
        board_size_label->setFont(font);

        horizontalLayout->addWidget(board_size_label);


        verticalLayout->addLayout(horizontalLayout);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        obstacle_num = new QSpinBox(verticalLayoutWidget);
        obstacle_num->setObjectName("obstacle_num");
        obstacle_num->setMaximum(16);
        obstacle_num->setSingleStep(2);

        horizontalLayout_2->addWidget(obstacle_num);


        verticalLayout->addLayout(horizontalLayout_2);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        black_player = new QRadioButton(verticalLayoutWidget);
        black_player->setObjectName("black_player");
        black_player->setCheckable(true);
        black_player->setChecked(true);

        horizontalLayout_4->addWidget(black_player);

        white_player = new QRadioButton(verticalLayoutWidget);
        white_player->setObjectName("white_player");
        white_player->setFont(font);

        horizontalLayout_4->addWidget(white_player);

        random = new QRadioButton(verticalLayoutWidget);
        random->setObjectName("random");

        horizontalLayout_4->addWidget(random);


        verticalLayout->addLayout(horizontalLayout_4);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(setting_dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, setting_dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, setting_dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(setting_dialog);
    } // setupUi

    void retranslateUi(QDialog *setting_dialog)
    {
        setting_dialog->setWindowTitle(QCoreApplication::translate("setting_dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("setting_dialog", "\353\263\264\353\223\234 \355\201\254\352\270\260", nullptr));
        board_size_label->setText(QCoreApplication::translate("setting_dialog", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("setting_dialog", "\354\236\245\354\225\240\353\254\274 \352\260\234\354\210\230", nullptr));
        label_5->setText(QCoreApplication::translate("setting_dialog", "\354\204\240\352\263\265 \355\224\214\353\240\210\354\235\264\354\226\264", nullptr));
        black_player->setText(QCoreApplication::translate("setting_dialog", "\355\235\221", nullptr));
        white_player->setText(QCoreApplication::translate("setting_dialog", "\353\260\261", nullptr));
        random->setText(QCoreApplication::translate("setting_dialog", "\353\254\264\354\236\221\354\234\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting_dialog: public Ui_setting_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_DIALOG_H
