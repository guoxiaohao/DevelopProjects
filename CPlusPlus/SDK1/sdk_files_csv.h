#pragma once

#include <fstream>
#include <stdint.h>
#include <string.h>

#include <string>

namespace CSVs
{

class FilesOpes
{
public:
    FilesOpes();
    ~FilesOpes();
public:
    void SetFileName(const std::string& filename);
    bool GetPerLine(std::string& perline); 
protected:
    std::string m_fileName;
    std::fstream m_fstream;
    uint64_t m_position;
};

}
