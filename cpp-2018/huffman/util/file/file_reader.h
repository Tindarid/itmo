#ifndef FILE_READER_H
#define FILE_READER_H
#include <string>
#include <fstream>

class file_reader {
    public:
        file_reader(std::string f);
        ~file_reader();
        bool ready();
        int read(char*, int);
        void reset();
    private:
        std::ifstream f;
        std::streamsize length;
        std::streamsize initialLength;
};

#endif
