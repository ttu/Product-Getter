#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget)
{
    maxPrice = -1;

    ui->setupUi(this);

    // Fill UI Controls
    ui->listView->setModel(&model);
    ui->listView->setItemDelegate(&deleg);

    ui->combo_MaxPrice->addItem("6");
    ui->combo_MaxPrice->addItem("8");
    ui->combo_MaxPrice->addItem("10");
    ui->combo_MaxPrice->addItem("12");
    ui->combo_MaxPrice->addItem("14");
    ui->combo_MaxPrice->addItem("16");
    ui->combo_MaxPrice->addItem("18");
    ui->combo_MaxPrice->addItem("20");
    ui->combo_MaxPrice->addItem("0");

    ui->combo_Cat->addItem("Blu-ray");
    ui->combo_Cat->addItem("PS3");
    ui->combo_Cat->addItem("Xbox360");
    ui->combo_Cat->addItem("T-Shirts");

    QObject::connect(ui->combo_MaxPrice,SIGNAL(currentIndexChanged(QString)),this,SLOT(maxPriceChanged()));
    QObject::connect(ui->btn_Stop,SIGNAL(clicked()),this,SLOT(stopButtonPressed()));
    QObject::connect(ui->btn_Start,SIGNAL(clicked()),this,SLOT(startButtonPressed()));
    QObject::connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
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

// Set item to screen
void Widget::setItem(Item newItem)
{
    QStandardItem *item = new QStandardItem(QString("%0 [%1 : %2]").arg(newItem.name).arg(newItem.price->toString()).arg(newItem.playTrade->toString()));
    model.setItem(model.rowCount(),item);
    urls.append(newItem.link);
    ui->lbl_ItemCount->setText(QString::number(model.rowCount()));

}

// Update page count
void Widget::setPageProgress(int pages)
{
    ui->lbl_PageCount->setText(QString::number(pages));
}

// Update total item count
void Widget::setTotalProgress(int total)
{
    ui->lbl_TotalCount->setText(QString::number(total));
}

// Page ready
void Widget::finshed()
{
    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
}

// Send new maxprice to manager and clear collections
void Widget::maxPriceChanged()
{
    try
    {
        maxPrice = ui->combo_MaxPrice->currentText().toDouble();
    }
    catch (...)
    {
        maxPrice = 0;
    }

    emit maxPriceChanged(maxPrice);
    ui->lbl_ItemCount->setText("0");
    urls.clear();
    model.clear();
}

void Widget::startButtonPressed()
{
    ui->lbl_ItemCount->setText("0");
    ui->lbl_PageCount->setText("0");
    ui->lbl_TotalCount->setText("0");
    urls.clear();
    model.clear();

    if (maxPrice == -1)
        maxPriceChanged();

    ui->btn_Start->setEnabled(false);
    ui->btn_Stop->setEnabled(true);
    emit startSignal(ui->combo_Cat->currentIndex(),maxPrice);
}

void Widget::stopButtonPressed()
{
    ui->btn_Start->setEnabled(true);
    ui->btn_Stop->setEnabled(false);
    emit stopSignal();
}

// Open browser window
void Widget::itemClicked(QModelIndex index)
{
    w.setUrl(QString("http://www.play.com%0").arg(urls[index.row()]));
    w.show();
    w.topLevelWidget();
}
