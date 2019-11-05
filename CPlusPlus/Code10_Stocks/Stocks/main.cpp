#include "pch.h"

extern guoxh::StockSort MyStockSort;

int main(int argc, char* argv[])
{
    std::cout << "------ start ------" << std::endl;

    if(!MyStockSort.Init("/mnt/d/DevelopEnvir/DevelopProjects/CPlusPlus/Code10_Stocks/Stocks/config/focus.json"))
    {
        std::cout << "Load failed" << std::endl;
    }
    MyStockSort.DisplayData();

    std::cout << "------ end ------" << std::endl;
    return 0;
}