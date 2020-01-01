#include "textcompare.h"
#include <QMap>

void TextCompare::resizeStringList(QStringList& list, int newSize)
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

QString TextCompare::longestCommonSubsequence(const QString& source, const QString& target)
{
    QMap<int, QMap<int, int>> l;
    for (int i = 0; i <= source.count(); i++) {
        for (int j = 0; j <= target.count(); j++) {
            if (i == 0 || j == 0) {
                l[i][j] = 0;
            } else if (source.at(i - 1) == target.at(j - 1)) {
                l[i][j] = l[i - 1][j - 1] + 1;
            } else {
                l[i][j] = std::max(l[i - 1][j], l[i][j - 1]);
            }
        }
    }

    int i = source.count();
    int j = target.count();
    int index = l[source.count()][target.count()];
    QString longestCommonSubsequence;
    while (i > 0 && j > 0) {
        if (source.at(i - 1) == target.at(j - 1)) {
            longestCommonSubsequence[index - 1] = source.at(i - 1);
            i--;
            j--;
            index--;
        } else if (l[i - 1][j] > l[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return longestCommonSubsequence;
}

QStringList TextCompare::longestCommonSubsequence(const QStringList& source, const QStringList& target)
{
    QMap<int, QMap<int, int>> l;
    for (int i = 0; i <= source.count(); i++) {
        for (int j = 0; j <= target.count(); j++) {
            if (i == 0 || j == 0) {
                l[i][j] = 0;
            } else if (source.at(i - 1) == target.at(j - 1)) {
                l[i][j] = l[i - 1][j - 1] + 1;
            } else {
                l[i][j] = std::max(l[i - 1][j], l[i][j - 1]);
            }
        }
    }

    int i = source.count();
    int j = target.count();
    int index = l[source.count()][target.count()];
    QStringList longestCommonSubsequence;
    resizeStringList(longestCommonSubsequence, qMax(i, j));
    while (i > 0 && j > 0) {
        if (source.at(i - 1) == target.at(j - 1)) {
            longestCommonSubsequence[index - 1] = source.at(i - 1);
            i--;
            j--;
            index--;
        } else if (l[i - 1][j] > l[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return longestCommonSubsequence;
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
