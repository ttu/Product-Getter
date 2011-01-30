#include <QtGui/QApplication>
#include "widget.h"
#include "itemmanager.h"
#include "item.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    ItemManager* m = new ItemManager();

    QObject::connect(m,SIGNAL(newItem(Item)),&w,SLOT(setItem(Item)));
    QObject::connect(m,SIGNAL(reportPageProgress(int)),&w,SLOT(setPageProgress(int)));
    QObject::connect(m,SIGNAL(reportTotalProgress(int)),&w,SLOT(setTotalProgress(int)));
    QObject::connect(m,SIGNAL(finished()),&w,SLOT(finshed()));
    QObject::connect(&w,SIGNAL(startSignal(int, double)),m,SLOT(startWorkers(int, double)));
    QObject::connect(&w,SIGNAL(stopSignal()),m,SLOT(stopWorkers()));
    QObject::connect(&w,SIGNAL(maxPriceChanged(double)),m,SLOT(getNewMaxPrice(double)));
    //m->start();
    w.show();

    return a.exec();
}
