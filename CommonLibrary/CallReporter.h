#pragma once

namespace IMFS
{
	class MethodCall;

	class CallResults
    {
	public:
		CallResults()
		{
			calls = 0;
			minInMicroseconds = 0;
			maxInMicroseconds = 0;
			totalMicroseconds = 0;
		}

		long calls;
        LONGLONG minInMicroseconds;
        LONGLONG maxInMicroseconds;
        LONGLONG totalMicroseconds;
    };
	
	class CallReporter
    {
	private:
		static IM::TraceLock ms_reportLock;
		std::map<string,CallResults> m_results;
		Timer m_timer;
        string m_reportName;
	public:
        CallReporter(const string& reportName);
        //static void timerHandler(object source, ElapsedEventArgs args);
		static void timerHandler(INT_PTR state);
		void Record(MethodCall& call);
        void Report();
        static string format(LONGLONG number);
    };

	
	class MethodCall 
    {
	private:
		const wchar_t *m_callName;
        bool m_ended;
        Stopwatch m_timer;
        LONGLONG m_microseconds;
        CallReporter& m_reporter;
		void _End(unsigned int ret, bool callCompleted);
	public:
        MethodCall(CallReporter& reporter, const wchar_t *callName);
        MethodCall(CallReporter& reporter, const wchar_t *callName, ConstNormalizedPathPtr path);
        MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1);
        MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1, const wchar_t *p2);
        MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1, ConstNormalizedPathPtr path);
        MethodCall(CallReporter& reporter, const wchar_t *callName, ConstNormalizedPathPtr path, ConstNormalizedPathPtr path2);
		~MethodCall();
		void End(ApiRet ret);
		void End(NtStatus ret, const wchar_t *revisedCallName);
		const LONGLONG& GetMicroseconds() { return m_microseconds; }
		const wchar_t *GetCallName() { return m_callName; }
	};


}