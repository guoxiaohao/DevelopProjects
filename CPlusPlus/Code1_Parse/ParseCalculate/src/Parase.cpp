#include "pch.h"

#include "Parase.h"
#include "ParaUse.h"

bool GetParseRet(const std::string& StrParse, float &fRet)
{
	CParaUse* lpUse = new CParaUse();
	lpUse->Parase(StrParse, fRet);
	delete lpUse; lpUse = nullptr;
	return true;
}
