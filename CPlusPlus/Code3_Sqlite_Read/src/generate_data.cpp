#include "pch.h"

#include "generate_data.h"

GenerateData::GenerateData()
{

}

GenerateData::~GenerateData()
{

}

void GenerateData::ResetInfos()
{
    vecInfos.clear();
    m_nTotal = 0;
}

void GenerateData::TravelGenerate(std::string& tHour, std::string& tArea)
{
    if(!global_sqlite.IsDBConnectOK())
    {
        return;
    }

    const char *szErrMsg;
    char sql[1024] = {0};
    sprintf(sql, "select * from super_days_table where hour='%s' and super_area='%s'", tHour.c_str(), tArea.c_str());

    sqlite3_stmt * stmt = NULL; 
    if( sqlite3_prepare_v2(global_sqlite.m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
    {
        m_nTotal++;
        std::cout << m_nTotal << std::endl;

        SupersInfo tmp;
        Location tmpLocate;
        NodeInfo tmpNode;
        bool bGet = false;
        
        std::string strValues;
        while( sqlite3_step(stmt) == SQLITE_ROW )
        {
            if(!bGet)
            {
                strValues = (char*)sqlite3_column_text(stmt, 1);
                tmp.strhour = atoi(strValues.c_str());
                strValues = (char*)sqlite3_column_text(stmt, 2);
                tmp.superarea = atoi(strValues.c_str());
                strValues = (char*)sqlite3_column_text(stmt, 3);
                tmp.areaweight = atof(strValues.c_str());
                strValues = (char*)sqlite3_column_text(stmt, 4);
                tmp.demand = atoi(strValues.c_str());

                strValues = (char*)sqlite3_column_text(stmt, 5);
                int nPos1 = strValues.find_first_of(',');
                int nPos2 = strValues.find_first_of(';');
                while(nPos1>0&&nPos2>2)
                {
                    std::string strlValue = strValues.substr(0, nPos2);
                    strValues = strValues.substr(nPos2+1, strValues.length());

                    std::string strvaluel = strlValue.substr(0, nPos1);
                    std::string strvaluer = strlValue.substr(nPos1+1, strlValue.length());

                    tmpLocate.x = atof(strvaluel.c_str());
                    tmpLocate.y = atof(strvaluer.c_str());
                    tmp.vecCenters.push_back(tmpLocate);
                    
                    nPos1 = strValues.find_first_of(',');
                    nPos2 = strValues.find_first_of(';');
                }
                bGet = true;
            }

            if(tmp.demand >0)
            {
                tmpNode.nlens = 0;

                strValues = (char*)sqlite3_column_text(stmt, 6);
                tmpNode.NodeWeight = atof(strValues.c_str());
                strValues = (char*)sqlite3_column_text(stmt, 7);
                tmpNode.NodeLocate.x = atof(strValues.c_str());
                strValues = (char*)sqlite3_column_text(stmt, 8);
                tmpNode.NodeLocate.y = atof(strValues.c_str());

                strValues = (char*)sqlite3_column_text(stmt, 9);
                int nPos3 = strValues.find_first_of(',');
                while(nPos3>0)
                {
                    std::string strval = strValues.substr(0, nPos3);

                    tmpNode.rValues[tmpNode.nlens] =  atoi(strval.c_str());
                    tmpNode.nlens++;
                    strValues = strValues.substr(nPos3+1, strValues.length());
                    nPos3 = strValues.find_first_of(',');
                }
                tmp.vecNodeInfos.push_back(tmpNode);
            }
        }

        vecInfos.push_back(tmp);
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cout << " Wrong -- select" << std::endl;
        return;
    }
}

void GenerateData::MySolutions()
{
    std::cout << "Solve Linear Program " << vecInfos.size() << std::endl;
    /* int fulCa = 300;
    int CH_count = 15;
    double equity=0.4;
    int days=24;
    int capacity = fulCa/CH_count;
    int rbase=40;
    int us[] = {24, 12, 8, 6, 4, 3, 2, 1}; */
}