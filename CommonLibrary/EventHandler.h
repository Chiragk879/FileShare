#pragma once

namespace IMFS
{
	class EventArgs;

	typedef void (__stdcall *handler_fn)(INT_PTR sender, DWORD_PTR ctx, EventArgs& args);

	// provides context for an event handler method 
	// (in C# this is what the delegate object does)
	struct EventDelegate
	{
		EventDelegate(handler_fn pFunction)
		{
			m_pFunction = pFunction;
			m_ctx = 0;
		}

		EventDelegate(handler_fn pFunction, DWORD_PTR ctx)
		{
			m_pFunction = pFunction;
			m_ctx = ctx;
		}

		handler_fn	m_pFunction;
		DWORD_PTR	m_ctx;
	};

	//
	// Provides an event handler for C++ code
	//
	class EventHandler
	{
		public:
			EventHandler& operator+=(const EventDelegate& handler);
			EventHandler& operator-=(const EventDelegate& pFunction);
			void InvokeAll(INT_PTR sender, EventArgs& args);

		public:
			EventHandler();
			EventHandler(const std::list<handler_fn>& allfuncs);
			~EventHandler();

		private:
			std::list<EventDelegate> handlers;
	};

	// Base (empty) EventArgs class that can be extended
	class EventArgs
	{
		public:
			virtual ~EventArgs();
	};
}