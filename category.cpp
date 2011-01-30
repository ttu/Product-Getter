#include "category.h"

Category::Category(QString body, QStringList vars)
{
    this->urlBody = body;
    this->subCats = vars;
    pageCounter = 1;
    currentSubCat = 0;
}

void Category::reset()
{
    pageCounter = 1;
    currentSubCat = 0;
}

QString Category::getNextPage()
{
    QString retVal;
    // Create page
    if (this->subCats.count() > 0)
        retVal = QString(urlBody).arg(subCats[currentSubCat]).arg(pageCounter);
    else
        retVal = QString(urlBody).arg(pageCounter);
    pageCounter += 1;

    return retVal;
}

bool Category::skipToNextSubCat()
{
    pageCounter = 1;
    currentSubCat += 1;
    if (currentSubCat > subCats.count()-1)
    {
        currentSubCat = -1;
        return false;
    }
    return true;
}
