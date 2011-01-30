#include "item.h"

Item::Item()
{
    price = new Money();
    playTrade = new Money();
}

ItemCollection::ItemCollection()
{}

void ItemCollection::addNewItems(QList<Item>items)
{
    // Add items to new items queue
    foreach(Item i, items)
        newItems.enqueue(i);

    // Add items to all items list
    allItems.append(items);
}

void ItemCollection::resetCollection()
{
    newItems.clear();

    // Add items to new items queue
    foreach(Item i, allItems)
        newItems.enqueue(i);
}

bool ItemCollection::hasNewItems()
{
    if (newItems.count() > 0)
        return true;

    return false;
}

Item ItemCollection::getNextItem()
{
    return newItems.dequeue();
}

Money::Money()
{
    this->euros = -1;
    this->cents = -1;
}

int Money::compareTo(Money m)
{
    if (this->euros == -1)
        return 1;

    if (this->euros>m.euros)
        return 1;
    else if (this->euros<m.euros)
        return -1;
    else
    {
        if (this->cents>m.cents)
            return 1;
        else if (this->cents<m.cents)
            return -1;
        else return 0;
    }
}

QString Money::toString()
{
    if (this->euros == -1)
        return "-1";

    return QString("%0.%1").arg(QString::number(this->euros)).arg(QString::number(this->cents));
}

