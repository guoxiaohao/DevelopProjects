#include "pch.h"

#include "ParaUse.h"

CParaUse m_ParaUse;

int main()
{
	std::string strPara = "6-2/1+(5/5*2+1)";
	assert(m_ParaUse.ParaString(strPara) == 7 );
	std::cout << "Right " << strPara << std::endl;

	strPara = "(6-2/1)+5/5*2+9";
	assert(m_ParaUse.ParaString(strPara) == 15 );
	std::cout << "Right " << strPara << std::endl;

	strPara = "66/33*22+21-23";
	assert(m_ParaUse.ParaString(strPara) == 42);
	std::cout << "Right " << strPara << std::endl;

	strPara = "66*77*(22-1+3+4/2*5)";
	assert(m_ParaUse.ParaString(strPara)==172788);
	std::cout << "Right " << strPara << std::endl;

	std::cout << COMPLIER_NAME << std::endl;
	system("pause");

	return 0;
}
