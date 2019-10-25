#include "LoadLibra.h"

#include <dlfcn.h>

bool MyLoadLibrary::Init()
{
    path_library_ = "/mnt/d/DevelopEnvir/DevelopProjects/CPlusPlus/Code10_Stocks/depends/libFTDataInterface.so";
    if (access(path_library_.c_str(), 0) != 0)
    {
        return false;
    }

    h_modules = dlopen(path_library_.c_str(), RTLD_LAZY);
    if(h_modules == nullptr)
	{
		return false;
	}

    FunctionExports.clear();
    FunctionExports.push_back("THS_RealtimeQuotes");
    FunctionExports.push_back("THS_iFinDLogin");
    FunctionExports.push_back("THS_iFinDLogout");
	for(std::size_t i = 0; i < FunctionExports.size(); i ++)
	{
        void* p = dlsym(h_modules, FunctionExports[i].c_str());
        if(p!=nullptr)
        {
            map_funcs.insert(std::make_pair(FunctionExports[i], p));
        }
	}

    return true;
}

void MyLoadLibrary::UnInit()
{
    if(h_modules!=nullptr)
    {
        dlclose(h_modules);
        h_modules = nullptr;
    }
}

void* MyLoadLibrary::GetLogin()
{
    auto items = map_funcs.find("THS_iFinDLogin");
    if(items==map_funcs.end())
    {
        return nullptr;
    }
    else
    {
        return items->second;
    }
}

void* MyLoadLibrary::GetLogout()
{
    auto items = map_funcs.find("THS_iFinDLogout");
    if(items==map_funcs.end())
    {
        return nullptr;
    }
    else
    {
        return items->second;
    }
}

void* MyLoadLibrary::GetRealtimeQuotes()
{
    auto items = map_funcs.find("THS_RealtimeQuotes");
    if(items==map_funcs.end())
    {
        return nullptr;
    }
    else
    {
        return items->second;
    }
}

void* MyLoadLibrary::GetHistoryQuotes()
{
    auto items = map_funcs.find("THS_HistoryQuotes");
    if(items==map_funcs.end())
    {
        return nullptr;
    }
    else
    {
        return items->second;
    }
}