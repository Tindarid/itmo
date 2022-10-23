#ifndef TRIGRAM_H
#define TRIGRAM_H

#include <QSet>
#include <QString>
#include <string>

struct TrigramSet {
    QString filename;
    QSet<quint32> trigrams;
    bool good;
    TrigramSet(QString const& str) {
        filename = str;
        good = false;
    }
    TrigramSet() {
        good = false;
    }
};

class TrigramUtil {
public:
    static const int MAX_TRIGRAMS = 20000;
    static const int MAX_LINE_LEN = 2000;
    //static const int MAX_FILE_SIZE = 1 << 30;

    static bool isSubset(TrigramSet const& subset, TrigramSet const& set);
    static void processFile(TrigramSet&);
    static TrigramSet processString(QString const& str);
    static bool isText(const TrigramSet& set);
private:
    static bool addFromString(TrigramSet& set, std::string const& str);
    static bool validUTF8(quint32 a, quint32 b);
};

#endif // TRIGRAM_H
