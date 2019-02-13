#pragma once

#include <queue>
#include <string>

class CMsgQueue
{
public:
	CMsgQueue();
	~CMsgQueue();
public:
	std::string GetFromQueue();
	void PushIntoQueue(std::string strs);
	int GetSize();
private:
	std::queue<std::string> m_queMsgs;
};
