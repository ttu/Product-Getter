#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QProcess>
#include <QAbstractItemView>
#include <QItemDelegate>

#include "item.h"
#include "itemwidget.h"
#include "browserwidget.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    BrowserWidget w;
    QStandardItemModel model;
    QItemDelegate deleg;
    double maxPrice;
    QList<QString> urls;
signals:
    void startSignal(int cat, double maxPrice);
    void stopSignal();
    void maxPriceChanged(double maxPrice);
private slots:
    void maxPriceChanged();
    void startButtonPressed();
    void stopButtonPressed();
    void itemClicked(QModelIndex index);
public slots:
    void setItem(Item newItem);
    void setPageProgress(int pages);
    void setTotalProgress(int total);
    void finshed();
};

#endif // WIDGET_H
