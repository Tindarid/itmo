#include "trigram.h"
#include <fstream>

bool TrigramUtil::isSubset(TrigramSet const& a, TrigramSet const& b) {
    for (auto it = a.trigrams.begin(); it != a.trigrams.end(); ++it) {
        if (b.trigrams.find(*it) == b.trigrams.end()) {
            return false;
        }
    }
    return true;
}

void TrigramUtil::processFile(TrigramSet& res) {
    std::string filename = res.filename.toStdString();
    std::ifstream in(filename);
    if (!in.is_open()) {
        return;
    }
    std::string cur;
    while (!in.eof()) {
        std::getline(in, cur);
        if (cur.length() > MAX_LINE_LEN) {
            res.trigrams.clear();
            return;
        }
        if (!addFromString(res, cur)) {
            return;
        }
        if (res.trigrams.size() > MAX_TRIGRAMS) {
            res.trigrams.clear();
            return;
        }
    }
    res.good = true;
}

TrigramSet TrigramUtil::processString(QString const& str) {
    TrigramSet res(str);
    addFromString(res, str.toStdString());
    res.good = true;
    return res;
}

bool TrigramUtil::addFromString(TrigramSet& set, std::string const& str) {
    size_t len = str.length();
    if (len < 3) {
        return true;
    }
    quint32 temp[MAX_LINE_LEN];
    for (size_t i = 0; i < len; ++i) {
        temp[i] = static_cast<quint8>(str[i]);
    }
    quint32 cur = (temp[0] << 8) | (temp[1]);
    for (size_t i = 2; i < len; ++i) {
        cur &= 0xFFFF;
        cur <<= 8;
        cur |= temp[i];
        if (!validUTF8((cur >> 8) & 0xFF, cur & 0xFF)) {
            return false;
        }
        set.trigrams.insert(cur);
    }
    return true;
}

bool TrigramUtil::validUTF8(quint32 a, quint32 b) {
    // 1-byte, must be followed by 1-byte or first of multi-byte
    if (a < 0x80) {
        return b < 0x80 || (0xc0 <= b && b < 0xf8);
    }
    // continuation byte, can be followed by nearly anything
    if (a < 0xC0) {
        return b < 0xf8;
    }
    // first of multi-byte, must be followed by continuation byte
    if (a < 0xF8) {
        return 0x80 <= b && b < 0xc0;
    }
    return false;
}

bool TrigramUtil::isText(const TrigramSet& set) {
    return set.good;
}
