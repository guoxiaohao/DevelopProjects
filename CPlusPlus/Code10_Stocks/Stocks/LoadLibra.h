#pragma once

#include <unistd.h>
#include <vector>
#include <string>
#include <map>

#include "TongHuaShunApis.h"

class MyLoadLibrary
{
public:
    bool Init();
    void UnInit();
public:
    void* GetLogin();
	void* GetLogout();
	void* GetRealtimeQuotes();
	void* GetHistoryQuotes();
protected:
    std::string path_library_;
    void* h_modules;
	std::vector<std::string> FunctionExports;
	std::map<std::string, void*> map_funcs;
};