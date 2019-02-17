#pragma once

#include <string>
#include <stack>

class CParaUse
{
public:
	CParaUse();
	~CParaUse();
public:
	bool Parase(const std::string & StrPara, float &fRet);
	bool Parase(char* szPar, float &fRet);
private:
	void TransferToContent(const std::string & StrPara);
	bool isRightChar(char ch);
	char szContent[255];
private:
	std::stack<float> m_StackFloat;
	std::stack<char> m_StackCh;
	void HandleCh(char chs);
private:
	int PrevValue(char chs);
	bool ComparePrev(char ch1, char ch2);
	float CalculateValue(float val1, float val2, char chs);
};
