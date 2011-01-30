#include "itemwidget.h"
#include "ui_itemwidget.h"

// NOT IN USE
ItemWidget::ItemWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ItemWidget)
{
    ui->setupUi(this);

    /*ui->label->setText(baseItem.name);
    ui->label_2->setText(baseItem.price->toString());
    ui->label_3->setText(baseItem.playTrade->toString());*/
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

void ItemWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
