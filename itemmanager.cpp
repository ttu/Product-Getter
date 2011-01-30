#include "itemmanager.h"

ItemManager::ItemManager()
{
    createCategories();
    htmlWorker = new HtmlWorker(this);
    itemWorker = new ItemWorker(this);
    collectionWorker = new CollectionWorker(this);
}

void ItemManager::run()
{
    this->moveToThread(this);

    counter = 0;

    QObject::connect(htmlWorker,SIGNAL(finished()), this, SLOT(htmlWorker_ready()));
    QObject::connect(itemWorker,SIGNAL(finished()), this, SLOT(itemWorker_ready()));
    QObject::connect(collectionWorker,SIGNAL(finished()), this, SLOT(collectionWorker_ready()));

    // Create first html worker and put it to work
    startHtmlWorker();
    
    running = true;
    while(this->running)
    {
        QThread::msleep(500);
    }
}

void ItemManager::startHtmlWorker()
{
    counter++;
    //nextPage = "http://www.play.com/Clothing/T-Shirts/-/2007/1288/3-/RegionHome.html?ob=rating&searchtype=genre&cur=258&cpage=" + QString::number(counter);

    htmlWorker->pageToRead = cats[selectedCat].getNextPage();
    htmlWorker->start();
}

void ItemManager::startItemWorker()
{
    if (itemWorker->isRunning())
        return; // Worker running, no need to start

    itemWorker->contentToProcess = workQueue.dequeue();
    itemWorker->start();
}

void ItemManager::startCollectionWorker()
{
    if (collectionWorker->isRunning())
        return; // Worker running, no need to start

    collectionWorker->itemsToCheck.append(this->newItems);
    this->newItems.clear();
    collectionWorker->start();
}

void ItemManager::htmlWorker_ready()
{
    // If worker stopped do nothing
    if (!running)
        return;

    // If page has data prcess it normally
    if (pageHasData(htmlWorker->pageContent))
    {
        // Add page to itemWorkers work queue
        workQueue.enqueue(htmlWorker->pageContent);
        updateProgress();
        // If itemWorker is waiting, kick it back to work
        if (itemWorker->waitingForWork)
            startItemWorker();
        // Get next page
        if (htmlWorker->waitingForWork)
            startHtmlWorker();
    }
    else
    {
        // If has more sub-categories take next
        if (cats[selectedCat].skipToNextSubCat())
        {
            updateProgress();
            // Get next page
            if (htmlWorker->waitingForWork)
                startHtmlWorker();
        }
        else
        {
            htmlWorker->noMoreWork = true;

            // If itemworker waiting for more data
            if (!itemWorker->isRunning())
            {
                itemWorker->noMoreWork = true;

                if (!collectionWorker->isRunning())
                {
                    finish();
                }
            }
        }
    }
}

void ItemManager::itemWorker_ready()
{
    // If worker stopped do nothing
    if (!running)
        return;

    this->newItems.append(itemWorker->itemCollection);
    startCollectionWorker();

    // Check is there some pages to process
    if (!workQueue.isEmpty())
    {
        startItemWorker();
    }
    else
    {
        // If htmlWorker has fineshed work, then all is done
        if (htmlWorker->noMoreWork)
        {
            itemWorker->noMoreWork = true;
        }
    }

}

void ItemManager::collectionWorker_ready()
{
    // If worker stopped do nothing
    if (!running)
        return;

    // Update screen
    updateTotalProgress();
    putItemsToScreen();

    // If new items on list, process those
    if (newItems.count() > 0)
    {
        startCollectionWorker();
    }
    else if (htmlWorker->noMoreWork && itemWorker->noMoreWork)
    {
        // Everything is ready
        finish();
    }
}

void ItemManager::putItemsToScreen()
{
    // QMetaObject::invokeMethod(label, SLOT(setText(const QString &)), Q_ARG(QString, "Hello"));
    // Pass items to controller
    while (collectionWorker->itemCollection.hasNewItems())
    {
        Item item = collectionWorker->itemCollection.getNextItem();

        // If maxprice is defined comapre price
        if (maxPrice.euros > 0)
        {
            int compare1 = item.price->compareTo(maxPrice);
            int compare2 = item.playTrade->compareTo(maxPrice);

            if (compare1 < 0 || compare2 < 0)
            {
                emit newItem(item);
            }
        }
        else
        {
            emit newItem(item);
        }
    }
}

void ItemManager::updateProgress()
{
    emit reportPageProgress(counter);
}

// Send total item count
void ItemManager::updateTotalProgress()
{
    emit reportTotalProgress(this->collectionWorker->itemCollection.allItems.count());
}

void ItemManager::finish()
{
    running = false;
    //this->finished();
    // Destruct workers?
}

bool ItemManager::pageHasData(QString data)
{
    // Just check that page contains data
    int start = data.indexOf("body");
    int end = data.lastIndexOf("<div class=\"browse wrap\" >");
    data = data.mid(start, end - start);

    QStringList items = data.split("<div class=\"slice\">");
    if (items.count() == 1)
        return false;

    return true;
}

void ItemManager::startWorkers(int category, double maxPrice)
{
    counter = 0;
    this->selectedCat = category;
    cats[selectedCat].reset();
    this->maxPrice.euros = maxPrice;
    this->maxPrice.cents = 0;
    this->start();
}

// Got new max price
void ItemManager::getNewMaxPrice(double maxPrice)
{
    this->maxPrice.euros = maxPrice;
    // Send collection items again
    collectionWorker->resetSentItems();

    updateTotalProgress();
    putItemsToScreen();
}

// Force stop workers
void ItemManager::stopWorkers()
{
    itemWorker->quit();
    htmlWorker->quit();

    this->running = false;
}

void ItemManager::createCategories()
{
    QStringList gameCats;
    gameCats.append("Adventure");
    gameCats.append("Arcade");
    gameCats.append("Driving+%2f+Racing");
    gameCats.append("Fighting");
    gameCats.append("Party+%2f+Family");
    gameCats.append("Platform");
    gameCats.append("Puzzle+%26+Mind+Games");
    gameCats.append("Rhythm+%2f+Music");
    gameCats.append("Role+Playing");
    gameCats.append("Shooter");
    gameCats.append("Simulation");
    gameCats.append("Sport");
    gameCats.append("Strategy");
    gameCats.append("Virtual+Life");

    QStringList blurayCats;
    blurayCats.append("602/810");
    blurayCats.append("604/812");
    blurayCats.append("605/813");
    blurayCats.append("609/817");
    blurayCats.append("610/818");
    blurayCats.append("611/819");
    blurayCats.append("612/820");
    blurayCats.append("613/821");
    blurayCats.append("615/823");
    blurayCats.append("616/824");
    blurayCats.append("617/825");
    blurayCats.append("2176/1443");
    blurayCats.append("619/827");
    blurayCats.append("620/828");
    blurayCats.append("621/829");
    blurayCats.append("623/831");
    blurayCats.append("624/832");
    blurayCats.append("626/834");


    cats.append(Category("http://www.play.com/DVD/Blu-ray/-/%0/3-/NowAvailable.html?searchtype=genre&cur=258&cpage=%1", blurayCats));
    cats.append(Category("http://www.play.com/Games/PlayStation3/6-/GenreBrowse.html?searchstring=%0&cur=258&cpage=%1", gameCats));
    cats.append(Category("http://www.play.com/Games/Xbox360/6-/GenreBrowse.html?searchstring=%0&cur=258&cpage=%1", gameCats));
    cats.append(Category("http://www.play.com/Clothing/T-Shirts/-/2007/1288/3-/RegionHome.html?ob=rating&searchtype=genre&cur=258&cpage=%0",QStringList()));

}
