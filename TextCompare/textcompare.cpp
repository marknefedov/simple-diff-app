#include "textcompare.h"
#include <QMap>

void TextCompare::resizeQStringList(QStringList& list, int newSize)
{
    int diff = newSize - list.size();
    if (diff > 0)
    {
        list.reserve(diff);
        while (diff>0)
        {
            list.append("");
            diff--;
        }
    }
    else if (diff < 0) list.erase(list.end() + diff, list.end());
}

QMap<int, QString> TextCompare::QStringListDifference(QStringList lcs, const QStringList& target)
{
    QMap<int, QString> differenceMap;

    for (int i = 0; i < target.count(); i++)
    {
        if (lcs.contains(target[i]))
            lcs.removeOne(target[i]);
        else differenceMap.insert(i, target[i]);
    }

    return differenceMap;
}
