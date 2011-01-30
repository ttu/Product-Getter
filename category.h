#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <qstringlist.h>

class Category
{
public:
    Category(QString urlBody, QStringList subCats);
    QString getNextPage();
    bool skipToNextSubCat();
    void reset();
private:
    QString urlBody;
    QStringList subCats;
    int currentSubCat;
    int pageCounter;
};

#endif // CATEGORY_H
