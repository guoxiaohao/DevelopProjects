#include "sdk_files_csv.h"


namespace CSVs
{

FilesOpes::FilesOpes()
{
    m_position = 0;
}

FilesOpes::~FilesOpes()
{
    
}

void FilesOpes::SetFileName(const std::string& filename)
{
    m_fileName = filename;
}

bool FilesOpes::GetPerLine(std::string& perline)
{
    if(m_fileName=="")
    {
        return false;
    }

    m_fstream.open(m_fileName.c_str(), std::ios::in);
    if(!m_fstream.is_open())
    {
        return false;
    }

    m_fstream.seekg(m_position, std::ios::beg);
    char szData[2048] = {0};
    if(!m_fstream.eof())
    {
        m_fstream.getline(szData, sizeof(szData)-1);
        m_position = m_fstream.tellg();
    }
    m_fstream.close();

    if(strlen(szData)>0)
    {
        perline = szData;
        return true;
    }
    else
    {
        return false;
    }
} 

}
