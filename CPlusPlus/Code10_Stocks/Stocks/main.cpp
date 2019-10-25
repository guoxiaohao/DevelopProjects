#include "pch.h"

extern MyLoadLibrary loads;

int main(int argc, char* argv[])
{
    std::cout << "------ start ------" << std::endl;
    if(loads.Init())
    {
        std::cout << "Load successfully" << std::endl;
    }
    else
    {
        std::cout << "Load failed" << std::endl;
    }

    int nRet;
    tonghuashun_login api_login = (tonghuashun_login)loads.GetLogin();
    if (api_login)
	{
		//nRet = api_login("ifind", "ifind");
        //std::cout << nRet << std::endl;
	}

    tonghuashun_logout api_logout = (tonghuashun_logout)loads.GetLogout();
    loads.UnInit();
    std::cout << "------ end ------" << std::endl;
    return 0;
}