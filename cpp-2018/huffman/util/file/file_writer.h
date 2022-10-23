#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <string>
#include <fstream>

class file_writer {
    public:
        file_writer(std::string f);
        ~file_writer();
        void write(char*, int);
    private:
        std::ofstream f;
};

#endif
