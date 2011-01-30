#ifndef ITEM_H
#define ITEM_H

#include <QList>
#include <QQueue>
#include <QString>

// Helper class for currency
class Money
{
public:
    Money();
    int euros;
    int cents;
    int compareTo(Money m);
    QString toString();
};

class Item
{
public:
    Item();
    QString image;
    QString name;
    QString link;
    Money *price;
    Money *playTrade;

    //int count;
};


class ItemCollection
{
public:
    ItemCollection();
    QList<Item> allItems;
    void addNewItems(QList<Item> items);
    void sort();
    bool hasNewItems();
    Item getNextItem();
    void resetCollection();
private:

    QQueue<Item> newItems;
};


#endif // ITEM_H
