#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QListWidget>


#include "item.h"

namespace Ui {
    class ItemWidget;
}

// NOT IN USE
class ItemWidget : public QWidget {
    Q_OBJECT
public:
    ItemWidget(QWidget *parent = 0);
    ~ItemWidget();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::ItemWidget *ui;
};

#endif // ITEMWIDGET_H
