#pragma once

#include <fstream>
#include <stdint.h>
#include <string.h>
#include <string>

namespace SDK_FILES
{

class FilesRead
{
public:
    FilesRead();
    ~FilesRead();
public:
    void SetFileName(char* filename);
    void SetFileName(const std::string& filename);
    bool GetPerLine(std::string& perline); 
protected:
    std::string m_fileName;
    std::fstream m_fstream;
    uint64_t m_position;
};

}
