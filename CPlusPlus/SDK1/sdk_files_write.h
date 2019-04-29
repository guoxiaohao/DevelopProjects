#pragma once

#include <fstream>
#include <stdint.h>
#include <string.h>
#include <string>

namespace SDK_FILES
{

class FilesWrite
{
public:
    FilesWrite();
    ~FilesWrite();
public:
    void SetFileName(char* filename);
    void SetFileName(const std::string& filename);
    bool TruncFile();
    bool WriteLine(char* perline);
    bool WriteLine(std::string& perline); 
protected:
    std::string m_fileName;
    std::fstream m_fstream;
};

}
