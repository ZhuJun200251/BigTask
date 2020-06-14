/********************************************************************************
** Form generated from reading UI file 'startfrom.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTFROM_H
#define UI_STARTFROM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartFrom
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *StartFrom)
    {
        if (StartFrom->objectName().isEmpty())
            StartFrom->setObjectName(QStringLiteral("StartFrom"));
        StartFrom->resize(640, 480);
        StartFrom->setStyleSheet(QString::fromUtf8("image: url(:/image/\347\225\214\351\235\242\350\203\214\346\231\257.png);"));
        pushButton = new QPushButton(StartFrom);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 250, 121, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(24);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QStringLiteral(""));
        pushButton_2 = new QPushButton(StartFrom);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 250, 121, 61));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(StartFrom);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(430, 250, 121, 61));
        pushButton_3->setFont(font);

        retranslateUi(StartFrom);

        QMetaObject::connectSlotsByName(StartFrom);
    } // setupUi

    void retranslateUi(QWidget *StartFrom)
    {
        StartFrom->setWindowTitle(QApplication::translate("StartFrom", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("StartFrom", "\347\254\254\344\270\200\345\205\263", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("StartFrom", "\347\254\254\344\272\214\345\205\263", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("StartFrom", "\347\254\254\344\270\211\345\205\263", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartFrom: public Ui_StartFrom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTFROM_H
