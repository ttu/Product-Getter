#ifndef WORKERS_H
#define WORKERS_H

#include <QThread>
#include <QObject>
#include <QList>
#include <QTime>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QStringList>
#include <QString>
#include <QIntValidator>
#include <math.h>

#include "item.h"


class Worker: public QThread
{
    Q_OBJECT
public:
    Worker(QThread *parent = 0);
    bool noMoreWork;
    virtual void run() = 0;
    // Not in use, always true
    bool waitingForWork;
};

class HtmlWorker: public Worker
{
    Q_OBJECT
public:
    HtmlWorker(QThread *parent = 0);
    QString pageToRead;
    QString pageContent;
    QNetworkAccessManager *nam;

    void run();
    bool waitingData;
private slots:
    void finishedSlot(QNetworkReply* reply);
};

class ItemWorker: public Worker
{
public:
    ItemWorker(QThread *parent = 0);
    QString contentToProcess;
    QList<Item> itemCollection;
    void run();
private:
    bool isNumber(QString str);
    void processContent(QString content);
    void getAmount(QString *amount, Money *money);
};

class CollectionWorker: public Worker
{
public:
    CollectionWorker(QThread *parent = 0);
    ItemCollection itemCollection;
    // Temporary collections
    QList<Item> itemsToCheck;
    QList<Item> itemsToAdd;
    void run();
    void resetSentItems();
private:
    void processItems();
};
#endif // WORKERS_H
