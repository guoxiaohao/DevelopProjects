#include "pch.h"

#include "sqlite_writedata.h"
#include "sdk_files_csv.h"
#include "handle_raw_data.h" 

int main(int argc, char** argv)
{
    std::string DBName = "/home/guoxy/DBSqlite/supers_days.db";
    SqlWrite sqlwrite;
    bool brets = sqlwrite.InitDBSqlite3(DBName);
    if(!brets)
    {
        std::cout << "Wrong -- DataBase Startup" << std::endl;
        return 1;
    }

    std::string fileName = "supers_days_16.csv";
    CSVs::FilesOpes readFile;
    readFile.SetFileName(fileName);

    HandleRawData handleDatas;
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
            handleDatas.RecvData(strData, std::bind(&SqlWrite::DealDataSuperdaystable, &sqlwrite, std::placeholders::_1));
        }
    }

    std::string strTableName = "super_days_table";
    int numbertablerows = sqlwrite.GetTableRowNumber(strTableName);
    std::cout << "File row number " << nTotal << std::endl;
    std::cout << "DB row number " << numbertablerows << std::endl;
    sqlwrite.UninitDBSqlite3();
    
    return 0;
};