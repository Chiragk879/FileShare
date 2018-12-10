#include "stdafx.h"

using namespace IMFS;

EventHandler& 
EventHandler :: operator+=(const EventDelegate& handler)
{
	handlers.push_front(handler);
	return *this;
}

EventHandler& 
EventHandler :: operator-=(const EventDelegate& handler)
{
	std::list<EventDelegate>::iterator iter = handlers.begin();
	while (iter != handlers.end())
	{
		handler_fn test = (*iter).m_pFunction;
		if (test == handler.m_pFunction)
		{
			handlers.erase(iter);
			return *this;
		}
		++iter;
	}

	return *this;
}

void 
EventHandler :: InvokeAll(INT_PTR sender, EventArgs& args)
{
	std::list<EventDelegate>::iterator iter = handlers.begin();
	while (iter != handlers.end())
	{
		EventDelegate& handler = *iter;
		handler_fn pFunction = handler.m_pFunction;
		(*pFunction)(sender, handler.m_ctx, args);
		++iter;
	}
}

EventHandler :: EventHandler()
{
}

EventHandler :: ~EventHandler()
{
}

EventArgs :: ~EventArgs()
{
}