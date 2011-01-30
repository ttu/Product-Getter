#include "workers.h"

Worker::Worker(QThread *parent):QThread(parent)
{
    // Try to get thread completed to this thread
    this->moveToThread(this);
    noMoreWork = false;
    waitingForWork = true;
}


HtmlWorker::HtmlWorker(QThread *parent):Worker(parent)
{
    pageContent = QString::null;

    //    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
    //             this, SLOT(finishedSlot(QNetworkReply*)));
}

// Get one page
void HtmlWorker::run()
{
    QEventLoop loop;    

    QUrl url(pageToRead);
    QNetworkRequest request(url);
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                     &loop, SLOT(quit()));
    QNetworkReply* reply = nam->get(request);

    loop.exec();

    finishedSlot(reply);
}

// Get HTML Response
void HtmlWorker::finishedSlot(QNetworkReply* reply)
{
    QString string;
    QByteArray bytes;
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 2: Reading bytes form the reply
        bytes = reply->readAll();  // bytes
        string = QString(bytes); // string
    }
    // Some http error received
    else
    {
        pageContent = QString::null;
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;

    pageContent = string;
}

ItemWorker::ItemWorker(QThread *parent):Worker(parent)
{}

// Process one page to items
void ItemWorker::run()
{
    //    waitingForWork = false;
    //    QTime midnight(0,0,0);
    //    long seed = midnight.secsTo(QTime::currentTime());
    //    srand(seed);
    //    long time = rand() % 20 * 1000;
    //    QThread::msleep(time);
    //
    //    waitingForWork = true;
    //    // Signal ready
    //    this->finished();

    // Clear old items on process new content
    itemCollection.clear();
    processContent(contentToProcess);
}

void ItemWorker::processContent(QString content)
{
    int start = content.indexOf("body");
    int end = content.lastIndexOf("<div class=\"browse wrap\" >");
    content = content.mid(start, end - start);

    QStringList items = content.split("<div class=\"slice\">");

    // First not valid item so start from 1
    for (int i = 1; i < items.length(); i++)
    {
        Item *item = new Item();

        // Get link to item, start from first href=" and ends in ">
        QString st = "href=\"";
        start = items[i].indexOf(st) + st.length();
        // Drop crap from start
        items[i] = items[i].mid(start);
        st = "\">";
        end = items[i].indexOf(st);
        QString link = items[i].mid(0, end);
        item->link = link;

        // Drop link off
        items[i] = items[i].mid(end);
        // Get first src=" and drop it off
        st = "src=\"";
        start = items[i].indexOf(st) + st.length();
        items[i] = items[i].mid(start);

        // Get image
        st = "src=\"";
        start = items[i].indexOf(st) + st.length();
        items[i] = items[i].mid(start);

        st = "\"";
        end = items[i].indexOf(st);
        QString image = items[i].mid(0, end);
        item->image = image;

        st = "<a";
        start = items[i].indexOf(st) + st.length();
        items[i] = items[i].mid(start);

        st = ">";
        start = items[i].indexOf(st) + st.length();
        items[i] = items[i].mid(start);

        st = "<";
        end = items[i].indexOf(st);
        QString name = items[i].mid(0, end);
        item->name = name;

        getAmount(&items[i],item->price);

        //item->price = getAmount(items[i]);
        // Skip pre-orders PlayTrades
        if (items[i].contains("Also Available"))
        {
            getAmount(&items[i],item->playTrade);
        }
        //item->playTrade = getAmount(items[i]);

        itemCollection.append(*item);
    }
}

// Generate Money object from string
void ItemWorker::getAmount(QString *amount, Money *retVal)
{
    //Money retVal;
    QString st = "EUR";
    int start = amount->indexOf(st) + st.length();
    *amount = amount->mid(start);

    st = "<";
    int end = amount->indexOf(st);
    QString price = amount->mid(0, end).trimmed();
    //price = price.replace(".", System.Globalization.CultureInfo.CurrentCulture.NumberFormat.CurrencyDecimalSeparator);

    QStringList list = price.split(".");

    if(list.length() == 2 && isNumber(list[0]) && isNumber(list[1]))
    {
        retVal->euros = list[0].toInt();
        retVal->cents = list[1].toInt();
    }
    else
    {
        retVal->euros = -1;
        retVal->cents = -1;
    }

    //amount = amount->mid(end);
}

// If string is number return true
bool ItemWorker::isNumber(QString str)
{
    int length = str.length();
    QString list[10] = {"0","1","2","3","4","5","6","7","8","9"};

    for (int i=0; i < length; i++)
    {
        QString compare = str.mid(i,1);
        bool found = false;

        for(int j=0; j< 10; j++)
        {
            if (QString::compare(compare, list[j],Qt::CaseInsensitive) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

CollectionWorker::CollectionWorker(QThread *parent):Worker(parent)
{}

// Process items to collection
void CollectionWorker::run()
{
    processItems();
}

void CollectionWorker::processItems()
{
    foreach(Item iToCheck, itemsToCheck)
    {
        // loop to check doubles, slow slow slow...
        // check that item has valid prices
        if (iToCheck.price->euros != -1 || iToCheck.playTrade->euros != -1)
        {
            bool add = true;

            // compare to all items and check if item already exists
            foreach (Item it,itemCollection.allItems)
            {
                // TODO: fix comparing proces
                if (QString::compare(it.name,iToCheck.name,Qt::CaseInsensitive) == 0)// && it.price->compareTo(*iToCheck.price) == 0 && it.playTrade->compareTo(*iToCheck.playTrade) == 0)
                {
                    add = false;
                    break;
                }
                else
                    add = true;
            }

            if (add)
                itemsToAdd.append(iToCheck);
        }
    }

    // Add new items to collection and clear temp collections
    itemCollection.addNewItems(itemsToAdd);
    itemsToAdd.clear();
    itemsToCheck.clear();
}

// Reset collection
void CollectionWorker::resetSentItems()
{
    itemCollection.resetCollection();
}
