#include "worker.h"
#include "trigram.h"
#include <QThread>
#include <fstream>
#include <algorithm>
#include <functional>

void Worker::doSearch(QVector<TrigramSet> const& files, QString const& pattern) {
    QThread* thread = QThread::currentThread();
    TrigramSet patternSet = TrigramUtil::processString(pattern);
    for (int i = 0; i < files.size(); ++i) {
        if (thread->isInterruptionRequested()) {
            break;
        }
        if (TrigramUtil::isSubset(patternSet, files[i])) {
            QString const& filename = files[i].filename;
            auto ans = findInFile(filename, pattern);
            if (!ans.empty()) {
                emit result(filename, ans);
            }
        }
    }
    emit searchingFinished();
}

QVector<QPair<QPair<int, int>, QString>> Worker::findInFile(QString const& filename, QString const& pattern) {
    QVector<QPair<QPair<int, int>, QString>> ans;
    std::ifstream in(filename.toStdString());
    if (!in.is_open()) {
        return ans;
    }
    std::string cur;
    std::string pat = pattern.toStdString();
    int number = 0;
    while (!in.eof()) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            return ans;
        }
        number++;
        std::getline(in, cur);
        int count = boyerMoore(cur, pat);
        if (count > 0) {
            ans.push_back(QPair<QPair<int, int>, QString>(QPair<int, int>(number, count), QString::fromStdString(cur)));
        }
    }
    return ans;
}

int Worker::bruteForce(std::string const& text, std::string const& pattern, size_t patlen) {
    int count = 0;
    for (size_t i = 0; i + patlen - 1 < text.length(); ++i) {
        if (text[i] == pattern[0]) {
            bool flag = true;
            for (size_t j = 0; j < patlen; ++j) {
                if (pattern[j] != text[i + j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                count++;
            }
        }
    }
    return count;
}

int Worker::boyerMoore(std::string const& text, std::string const& pattern) {
    int ans = 0;
    auto it = std::search(text.begin(), text.end(),
                       std::boyer_moore_searcher(
                           pattern.begin(), pattern.end()));
    while (it != text.end()) {
        ans++;
        it = std::search(it + 1, text.end(),
                       std::boyer_moore_searcher(
                           pattern.begin(), pattern.end()));
    }
    return ans;
}
