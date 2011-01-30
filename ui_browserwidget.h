/********************************************************************************
** Form generated from reading UI file 'browserwidget.ui'
**
** Created: Sat Feb 13 08:45:21 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSERWIDGET_H
#define UI_BROWSERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_BrowserWidget
{
public:
    QWebView *webView;

    void setupUi(QWidget *BrowserWidget)
    {
        if (BrowserWidget->objectName().isEmpty())
            BrowserWidget->setObjectName(QString::fromUtf8("BrowserWidget"));
        BrowserWidget->resize(800, 420);
        webView = new QWebView(BrowserWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(10, 10, 780, 400));
        webView->setUrl(QUrl("about:blank"));

        retranslateUi(BrowserWidget);

        QMetaObject::connectSlotsByName(BrowserWidget);
    } // setupUi

    void retranslateUi(QWidget *BrowserWidget)
    {
        BrowserWidget->setWindowTitle(QApplication::translate("BrowserWidget", "PlayDotCom Browser", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BrowserWidget: public Ui_BrowserWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSERWIDGET_H
