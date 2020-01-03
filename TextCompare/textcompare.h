#ifndef TEXTCOMPARE_H
#define TEXTCOMPARE_H

#include <QStringList>
#include <QMap>
#include <QString>

namespace TextCompare
{    
    void resizeQStringList(QStringList& list, int newSize);
    QMap<int, QString> QStringListDifference(QStringList source, const QStringList& target);

    template<typename T>
    T longestCommonSubsequence(const T& source, const T& target)
    {
        {
            QMap<int, QMap<int, int>> l;
            for (int i = 0; i <= source.count(); i++) {
                for (int j = 0; j <= target.count(); j++) {
                    if (i == 0 || j == 0) {
                        l[i][j] = 0;
                    } else if (source.at(i - 1) == target.at(j - 1)) {
                        l[i][j] = l[i - 1][j - 1] + 1;
                    } else {
                        l[i][j] = qMax(l[i - 1][j], l[i][j - 1]);
                    }
                }
            }

            int i = source.count();
            int j = target.count();
            int index = l[source.count()][target.count()];
            T longestCommonSubsequence;
            resizeQStringList(longestCommonSubsequence, qMax(i, j));
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
    }
}

#endif // TEXTCOMPARE_H
