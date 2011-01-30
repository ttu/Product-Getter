#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>

namespace Ui {
    class BrowserWidget;
}

class BrowserWidget : public QWidget {
    Q_OBJECT
public:
    BrowserWidget(QWidget *parent = 0);
    ~BrowserWidget();
    void setUrl(QString url);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::BrowserWidget *ui;
};

#endif // BROWSERWIDGET_H
