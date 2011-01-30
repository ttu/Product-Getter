#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <iostream>
#include <QObject>
#include <QQueue>
#include <QStringList>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "workers.h"
#include "item.h"
#include "category.h"


class ItemManager: public QThread
{
    Q_OBJECT
public:
    ItemManager();
    void run();

private:
    bool running;
    // Html pages for itemworker to process
    QQueue<QString> workQueue;
    // New items for collectionworker to process
    QList<Item> newItems;
    //QStringList urlList;
    //QString nextPage;
    HtmlWorker* htmlWorker;
    ItemWorker* itemWorker;
    CollectionWorker* collectionWorker;
    int counter;
    QList<Category> cats;
    void startHtmlWorker();
    void startItemWorker();
    void startCollectionWorker();
    void putItemsToScreen();
    void updateProgress();
    void updateTotalProgress();
    void finish();
    void createCategories();
    bool pageHasData(QString page);
    bool working;
    Money maxPrice;
    int selectedCat;
signals:
    void newItem(Item newItem);
    void reportPageProgress(int i);
    void reportTotalProgress(int i);
public slots:
    void startWorkers(int cat, double maxPrice);
    void stopWorkers();
    void getNewMaxPrice(double maxPrice);
private slots:
    void htmlWorker_ready();
    void itemWorker_ready();
    void collectionWorker_ready();
};

#endif // ITEMMANAGER_H
