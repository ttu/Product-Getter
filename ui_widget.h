/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Sat Feb 13 09:37:37 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *lbl_PageCount;
    QPushButton *btn_Start;
    QListView *listView;
    QComboBox *combo_MaxPrice;
    QPushButton *btn_Stop;
    QComboBox *combo_Cat;
    QLabel *label;
    QLabel *label_2;
    QLabel *lbl_ItemCount;
    QLabel *lbl_TotalCount;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 418);
        lbl_PageCount = new QLabel(Widget);
        lbl_PageCount->setObjectName(QString::fromUtf8("lbl_PageCount"));
        lbl_PageCount->setGeometry(QRect(80, 30, 41, 31));
        QFont font;
        font.setPointSize(16);
        lbl_PageCount->setFont(font);
        lbl_PageCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btn_Start = new QPushButton(Widget);
        btn_Start->setObjectName(QString::fromUtf8("btn_Start"));
        btn_Start->setGeometry(QRect(600, 10, 81, 41));
        QFont font1;
        font1.setPointSize(14);
        btn_Start->setFont(font1);
        listView = new QListView(Widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setEnabled(true);
        listView->setGeometry(QRect(10, 71, 771, 331));
        listView->setFont(font1);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setProperty("isWrapping", QVariant(false));
        listView->setWordWrap(true);
        combo_MaxPrice = new QComboBox(Widget);
        combo_MaxPrice->setObjectName(QString::fromUtf8("combo_MaxPrice"));
        combo_MaxPrice->setGeometry(QRect(450, 10, 111, 41));
        combo_MaxPrice->setFont(font1);
        btn_Stop = new QPushButton(Widget);
        btn_Stop->setObjectName(QString::fromUtf8("btn_Stop"));
        btn_Stop->setEnabled(false);
        btn_Stop->setGeometry(QRect(700, 10, 81, 41));
        btn_Stop->setFont(font1);
        combo_Cat = new QComboBox(Widget);
        combo_Cat->setObjectName(QString::fromUtf8("combo_Cat"));
        combo_Cat->setGeometry(QRect(210, 10, 201, 41));
        combo_Cat->setFont(font1);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 71, 31));
        label->setFont(font);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 71, 31));
        label_2->setFont(font);
        lbl_ItemCount = new QLabel(Widget);
        lbl_ItemCount->setObjectName(QString::fromUtf8("lbl_ItemCount"));
        lbl_ItemCount->setGeometry(QRect(80, 0, 41, 31));
        lbl_ItemCount->setFont(font);
        lbl_ItemCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lbl_TotalCount = new QLabel(Widget);
        lbl_TotalCount->setObjectName(QString::fromUtf8("lbl_TotalCount"));
        lbl_TotalCount->setGeometry(QRect(140, 0, 41, 31));
        lbl_TotalCount->setFont(font);
        lbl_TotalCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 0, 21, 31));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "PlayDotCom", 0, QApplication::UnicodeUTF8));
        lbl_PageCount->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        btn_Start->setText(QApplication::translate("Widget", "Start", 0, QApplication::UnicodeUTF8));
        btn_Stop->setText(QApplication::translate("Widget", "Stop", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "Pages", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "Items", 0, QApplication::UnicodeUTF8));
        lbl_ItemCount->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        lbl_TotalCount->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "/", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
