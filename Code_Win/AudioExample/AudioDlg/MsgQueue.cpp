#include "stdafx.h"
#include "MsgQueue.h"



CMsgQueue::CMsgQueue()
{
}

CMsgQueue::~CMsgQueue()
{
}

std::string CMsgQueue::GetFromQueue()
{
	std::string m_String = "";
	m_String = m_queMsgs.front();
	m_queMsgs.pop();

	return m_String;
}

void CMsgQueue::PushIntoQueue(std::string strs)
{
	m_queMsgs.push(strs);
}

int CMsgQueue::GetSize()
{
	return m_queMsgs.size();
}