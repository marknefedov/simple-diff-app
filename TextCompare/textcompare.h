#ifndef TEXTCOMPARE_H
#define TEXTCOMPARE_H

#include <QStringList>
#include <QMap>
#include <QString>

namespace TextCompare
{    
    void resizeStringList(QStringList& list, int newSize);
    QString  longestCommonSubsequence(const QString& source, const QString& target);
    QStringList longestCommonSubsequence(const QStringList& source, const QStringList& target);
    QMap<int, QString> QStringListDifference(QStringList source, const QStringList& target);
}

#endif // TEXTCOMPARE_H
