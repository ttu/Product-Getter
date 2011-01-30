/********************************************************************************
** Form generated from reading UI file 'itemwidget.ui'
**
** Created: Sat Feb 13 08:45:21 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMWIDGET_H
#define UI_ITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_ItemWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWebView *webView;

    void setupUi(QWidget *ItemWidget)
    {
        if (ItemWidget->objectName().isEmpty())
            ItemWidget->setObjectName(QString::fromUtf8("ItemWidget"));
        ItemWidget->resize(400, 99);
        label = new QLabel(ItemWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 10, 261, 16));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(ItemWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 40, 261, 16));
        label_2->setFont(font);
        label_3 = new QLabel(ItemWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 70, 261, 16));
        label_3->setFont(font);
        webView = new QWebView(ItemWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(10, 10, 101, 81));
        webView->setUrl(QUrl("about:blank"));

        retranslateUi(ItemWidget);

        QMetaObject::connectSlotsByName(ItemWidget);
    } // setupUi

    void retranslateUi(QWidget *ItemWidget)
    {
        ItemWidget->setWindowTitle(QApplication::translate("ItemWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ItemWidget", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ItemWidget", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ItemWidget", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ItemWidget: public Ui_ItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMWIDGET_H
