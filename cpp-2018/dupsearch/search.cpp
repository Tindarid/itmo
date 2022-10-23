#include "search.h"
#include <QDirIterator>
#include <QCryptographicHash>
#include <QMap>
#include <QVector>
#include <QThread>

void Search::doSearch(QString const& dir) {
    emit progressState(0);
    QDirIterator it(dir, QDir::Hidden | QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QVector<QString> filenames;
    while (it.hasNext()) {
        filenames.push_back(it.next());
    }

    QMap<qint64, QVector<QString>> groups;
    for (QString filename : filenames) {
        QFileInfo info(filename);
        qint64 filesize = info.size();
        auto it = groups.find(filesize);
        if (it != groups.end()) {
            it->push_back(filename);
        } else {
            QVector<QString> temp;
            temp.push_back(filename);
            groups.insert(filesize, temp);
        }
        if (QThread::currentThread()->isInterruptionRequested()) {
            emit finished();
            return;
        }
    }

    bool flag = false;
    int curState = 1;
    QCryptographicHash sha(QCryptographicHash::Sha3_256);
    for (auto it = groups.begin(); it != groups.end(); ++it, ++curState) {
        if (it->size() <= 1) {
            continue;
        }
        QMap<QByteArray, QVector<QFileInfo>> hashes;
        for (QString filename : *it) {
            sha.reset();
            QFile file(filename);
            if (file.open(QIODevice::ReadOnly)) {
                sha.addData(&file);
            }
            QByteArray res = sha.result();
            auto st = hashes.find(res);
            if (st != hashes.end()) {
                st->push_back(QFileInfo(filename));
            } else {
                QVector<QFileInfo> temp;
                temp.push_back(QFileInfo(filename));
                hashes.insert(res, temp);
            }
            if (QThread::currentThread()->isInterruptionRequested()) {
                emit finished();
                return;
            }
        }
        QDir directory(dir);
        for (auto st = hashes.begin(); st != hashes.end(); ++st) {
            if (st->size() > 1) {
                flag = true;
                emit dupseq(directory, *st);
            }
        }
        emit progressState(100 * curState / groups.size());
        if (QThread::currentThread()->isInterruptionRequested()) {
            emit finished();
            return;
        }
    }
    emit progressState(100);
    emit finished();
}
