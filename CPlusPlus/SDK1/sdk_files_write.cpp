#include "sdk_files_write.h"


namespace SDK_FILES
{

FilesWrite::FilesWrite()
{
}

FilesWrite::~FilesWrite()
{
    if(m_fstream.is_open())
    {
        m_fstream.close();
    }
}

void FilesWrite::SetFileName(char* filename)
{
    m_fileName = filename;
}

void FilesWrite::SetFileName(const std::string& filename)
{
    m_fileName = filename;
}

bool FilesWrite::TruncFile()
{
    if(m_fileName=="")
    {
        return false;
    }

    m_fstream.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);
    if(m_fstream.is_open())
    {
        m_fstream.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool FilesWrite::WriteLine(char* perline)
{
    std::string strPerLine = perline;
    return WriteLine(strPerLine);
}

bool FilesWrite::WriteLine(std::string& perline)
{
    if(m_fileName=="")
    {
        return false;
    }

    m_fstream.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    if(!m_fstream.is_open())
    {
        return false;
    }

    m_fstream << perline.c_str();
    m_fstream << "\n";
    m_fstream.close();

    return true;
} 

}
