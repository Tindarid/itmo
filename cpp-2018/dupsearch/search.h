#ifndef SEARCH_H
#define SEARCH_H

#include <QDir>

class Search : public QObject
{
    Q_OBJECT

signals:
    void dupseq(QDir const& dir, QVector<QFileInfo> duplicates);
    void progressState(int progress);
    void finished();

public slots:
    void doSearch(QString const& dir);
};

#endif // SEARCH_H
