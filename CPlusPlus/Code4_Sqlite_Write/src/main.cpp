#include "pch.h"

#include "sdk_files_csv.h"
#include "handle_raw_data.h" 
#include "sqlite_writedata.h"

int main(int argc, char** argv)
{
    std::string DBName1 = "/home/guoxy/DBSqlite/supers_days.db";
    std::string DBName2 = "/home/guoxy/DBSqlite/teacher_infos.db";

    bool bret1 = global_sqlite1.InitSqlite(DBName1);
    bool bret2 = global_sqlite2.InitSqlite(DBName2);
    if(!bret1||!bret2)
    {
        if(bret1)
        {
            global_sqlite1.UninitSqlite();
        }
        if(bret2)
        {
            global_sqlite2.UninitSqlite();
        }
        std::cout << "Wrong -- DataBase Startup" << std::endl;
        return 1;
    }

    std::string fileName1 = "supers_days_16.csv";
    std::string fileName2 = "ResultData.txt";

    CSVs::FilesOpes readFile1;
    CSVs::FilesOpes readFile2;
    readFile1.SetFileName(fileName1);
    readFile2.SetFileName(fileName2);
    
    HandleRawData1 handleDatas1;
    SqlWrite1 sqlwrite1;
    HandleRawData2 handleDatas2;
    SqlWrite2 sqlwrite2;

    //get everyline in file
    /*
    uint32_t nTotal = 0;
    while(true)
    {
        std::string strData;
        bool bRet = readFile1.GetPerLine(strData);
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
            handleDatas1.RecvData(strData, std::bind(&SqlWrite1::DealDataSuperdaystable, &sqlwrite1, std::placeholders::_1));
        }
    }
    
    //get everyline in file
    while(true)
    {
        std::string strData;
        bool bRet = readFile2.GetPerLine(strData);
        if(!bRet)
        {
            break;
        }
        
        handleDatas2.RecvData(strData, std::bind(&SqlWrite2::DealDataSuperdaystable, &sqlwrite2, std::placeholders::_1));
    }
    */
    
    int nRowNums = 0;
    std::string strTableName1 = "super_days_table";
    nRowNums = sqlwrite1.GetTableRowNumber(strTableName1);
    if(nRowNums>=0)
    {
        std::cout << strTableName1 << " Row number " << nRowNums << std::endl;
    }
    else
    {
        std::cout << strTableName1 << " Wrong" << std::endl;
    }

    std::string strTableName2 = "teacher_info_table";
    nRowNums = sqlwrite2.GetTableRowNumber(strTableName2);
    if(nRowNums>=0)
    {
        std::cout << strTableName2 << " Row number " << nRowNums << std::endl;
    }
    else
    {
        std::cout << strTableName2 << " Wrong" << std::endl;
    }
    
    global_sqlite1.UninitSqlite();
    global_sqlite2.UninitSqlite();
    
    return 0;
};