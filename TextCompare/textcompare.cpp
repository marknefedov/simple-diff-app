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

QString TextCompare::RightTrimm(const QString& str)
{
     int n = str.size() - 1;
     for (; n >= 0; --n) {
       if (!str.at(n).isSpace()) {
         return str.left(n + 1);
       }
     }
     return "";
   }

QMap<int, QString> TextCompare::QStringListDifference(QStringList source, const QStringList& target)
{
    QMap<int, QString> differenceMap;

    for (int i = 0; i < target.count(); i++)
    {
        if (source.contains(target[i]))
            source.removeOne(target[i]);
        else differenceMap.insert(i, target[i]);
    }

    return differenceMap;
}

QPair<QList<int>, QList<int>> TextCompare::FindDifferentLines(const QStringList& firstText, const QStringList& secondText)
{
    QPair<QList<int>, QList<int>> diffs;
    QStringList commonText = longestCommonSubsequence<QStringList>(firstText, secondText);
    QStringList copyCommonText = commonText;

    for (int i = 0; i < firstText.count(); i++)
    {
        if (commonText.contains(firstText[i]))
            commonText.removeOne(firstText[i]);
        else diffs.first.append(i);
    }


    for (int i = 0; i < secondText.count(); i++)
    {
        if (copyCommonText.contains(secondText[i]))
            copyCommonText.removeOne(secondText[i]);
        else diffs.second.append(i);
    }

    return diffs;
}
