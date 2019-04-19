#include "pch.h"

#include <assert.h>
#include "Parase.h"

int main(int argc, char** argv)
{
    std::cout << "Main Function" << std::endl;
    
	std::string strPara;
	float fRets;
	int nRest;
	
	strPara = "6-2/1+(5/5*2+1)";
	GetParseRet(strPara, fRets);
	nRest = (int)fRets;
	assert( nRest == 7 );
	std::cout << "Right " << strPara << std::endl;

	strPara = "(6-2/1)+5/5*2+9";
	GetParseRet(strPara, fRets);
	nRest = (int)fRets;
	assert( nRest == 15 );
	std::cout << "Right " << strPara << std::endl;

	strPara = "66/33*22+21-23";
	GetParseRet(strPara, fRets);
	nRest = (int)fRets;
	assert( nRest == 42);
	std::cout << "Right " << strPara << std::endl;

	strPara = "66*77*(22-1+3+4/2*5)";
	GetParseRet(strPara, fRets);
	nRest = (int)fRets;
	assert( nRest == 172788);
	std::cout << "Right " << strPara << std::endl;
	
    return 0;
}
