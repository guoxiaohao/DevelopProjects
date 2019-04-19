#include "pch.h"

#include "ParaUse.h"
#include "string.h"

CParaUse::CParaUse()
{
}

CParaUse::~CParaUse()
{
}

bool CParaUse::Parase(char* szPar, float &fRet)
{
	std::string StrUse = szPar;

	return Parase(StrUse, fRet);
}

bool CParaUse::Parase(const std::string & StrPara, float &fRet)
{
	while (!m_StackFloat.empty())
	{
		m_StackFloat.pop();
	}
	while (!m_StackCh.empty())
	{
		m_StackCh.pop();
	}
	TransferToContent(StrPara);

	char *p1 = nullptr;
	char *p2 = nullptr;
	p1 = szContent; p2 = szContent;
	while (*p2 != 0)
	{
		char ch = *p2;
		if (ch >= '0' && ch <= '9')
		{
			p2++;
			continue;
		}
		else
		{
			if (p1 == p2)
			{
				p1++;
				p2++;
				HandleCh(ch);//Operator Stack Push And Value Ope
			}
			else
			{
				char sznum[255] = { 0 };
				memcpy(sznum, p1, p2 - p1);
				m_StackFloat.push(atof(sznum));//Value Stack Push
				p2++;
				p1 = p2;
			
				HandleCh(ch);//Operator Stack Push And Value Ope
			}
		}
	}
	if (p1 != p2)
	{
		char sznum[255] = { 0 };
		memcpy(sznum, p1, p2 - p1);
		m_StackFloat.push(atof(sznum));//Value Stack Push
	}

	while (m_StackCh.size() > 0)
	{
		char tms = m_StackCh.top();
		m_StackCh.pop();

		float m1 = m_StackFloat.top();
		m_StackFloat.pop();
		float m2 = m_StackFloat.top();
		m_StackFloat.pop();

		float m_value1 = CalculateValue(m1, m2, tms);
		m_StackFloat.push(m_value1);
	}
	
	fRet = m_StackFloat.top();
	m_StackFloat.pop();
	return true;
}

void CParaUse::TransferToContent(const std::string & StrPara)
{
	memset(szContent, 0, sizeof(szContent));
	char szTemp[255] = {0};
	strcpy(szTemp, StrPara.c_str());
	for (int i = 0, j = 0; i < strlen(szTemp); i++)
	{
		if (isRightChar(szTemp[i]))
		{
			szContent[j] = szTemp[i];
			j++;
		}
	}
}

bool CParaUse::isRightChar(char ch)
{
	if (ch=='(' || ch==')'|| ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| (ch>=48&&ch<=57))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CParaUse::HandleCh(char chs)
{
	if (m_StackCh.size() == 0 || chs == '(')
	{
		m_StackCh.push(chs);
		return;
	}

	if (chs == ')')
	{
		char tms = m_StackCh.top();
		while (tms != '(')
		{
			m_StackCh.pop();
			float m1 = m_StackFloat.top();
			m_StackFloat.pop();
			float m2 = m_StackFloat.top();
			m_StackFloat.pop();
			float m_value1 = CalculateValue(m1, m2, tms);
			m_StackFloat.push(m_value1);
			tms = m_StackCh.top();
		}

		m_StackCh.pop();
		return;
	}

	char tmpchs = m_StackCh.top();
	while ( ComparePrev(tmpchs, chs) )
	{
		m_StackCh.pop();
		float m1 = m_StackFloat.top();
		m_StackFloat.pop();
		float m2 = m_StackFloat.top();
		m_StackFloat.pop();

		float m_value1 = CalculateValue(m1, m2, tmpchs);
		m_StackFloat.push(m_value1);

		if (m_StackCh.size()==0)
		{
			break;
		}
		tmpchs = m_StackCh.top();
	}
	m_StackCh.push(chs);
	return;
}

int CParaUse::PrevValue(char chs)
{
	int nRet = -1;
	switch (chs)
	{
		case '+':
			nRet = 1;
			break;
		case '-':
			nRet = 2;
			break;
		case '*':
			nRet = 3;
			break;
		case '/':
			nRet = 4;
			break;
		default:
			break;
	}

	return nRet;
}

bool CParaUse::ComparePrev(char ch1, char ch2)
{
	if ( PrevValue(ch2) < PrevValue(ch1) )
	{
		return true;
	}
	return false;
}

float CParaUse::CalculateValue(float val1, float val2, char chs)
{
	switch (chs)
	{
	case '*':
		return val2 * val1;
	case '/':
		return val2 / val1;
	case '+':
		return val2 + val1;
	default:
		return val2 - val1;
	}
}