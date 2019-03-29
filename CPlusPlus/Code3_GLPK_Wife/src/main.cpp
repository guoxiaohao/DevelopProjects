#include "pch.h"

#include "sdk_files_csv.h"
#include "handle_raw_data.h"

int main(int argc, char** argv)
{
    std::cout << glp_version() << std::endl;
    std::string fileName = "supers_days_16.csv";

    CSVs::FilesOpes readFile;
    HandleRawData handleDatas;
    readFile.SetFileName(fileName);

    uint32_t nTotal = 0;
    while(true)
    {
        std::string strData;
        bool bRet = readFile.GetPerLine(strData);
        if(!bRet)
        {
            break;
        }
        nTotal ++;

        if(nTotal==1)
        {
            continue;
        }
        else
        {
            handleDatas.RecvData(strData);
        }
    }
    std::cout << "Total row number of file " << nTotal << std::endl;
    
    return 0;
};