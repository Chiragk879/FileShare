#include "stdafx.h"

using namespace IMFS;

IM::TraceLock CallReporter::ms_reportLock(L"CallReporter");

CallReporter::CallReporter(const string& reportName)
{
    m_reportName = reportName;
    m_timer.SetInterval(3600000);
    m_timer.SetElapsed(timerHandler, (INT_PTR)this);
    m_timer.Start();
}

void CallReporter::timerHandler(INT_PTR state)
{
    CallReporter* pReporter = (CallReporter*)state;
    pReporter->Report();
}


void CallReporter::Record(MethodCall& call)
{
    AUTO_LOCK(&ms_reportLock);
    string callName(call.GetCallName());
    std::map<string, CallResults>::iterator it = m_results.find(callName);
    if (it == m_results.end())
    {
        m_results.insert(std::make_pair(callName, CallResults()));
        it = m_results.find(callName);
    }

    CallResults& cr = it->second;
    cr.calls++;
    cr.totalMicroseconds += call.GetMicroseconds();
    if (call.GetMicroseconds() > cr.maxInMicroseconds)
        cr.maxInMicroseconds = call.GetMicroseconds();
    if ((cr.minInMicroseconds == 0) || (call.GetMicroseconds() < cr.minInMicroseconds))
        cr.minInMicroseconds = call.GetMicroseconds();
}

void CallReporter::Report()
{
    if (!LogMgr::IsInfoEnabled())
        return;

    AUTO_LOCK(&ms_reportLock);

    // the stl map keys are found to be sorted by default.
    // so copy to vector and sort again is not required
    /*
    ICollection keys = m_results.Keys;
    ArrayList sortedKeys = new ArrayList(keys);
    sortedKeys.Sort();
    */
    bool first = true;
    long totalCalls = 0;
    std::map<string, CallResults>::iterator it;
    it = m_results.begin();
    while (it != m_results.end())
    {
        string callName = it->first;
        CallResults& cr = (CallResults&)it->second;

        totalCalls += cr.calls;

        int len = callName.Length();
        for (size_t i = len; i < 40; i++)
            callName += L" ";

        if (first)
        {
            IMLOG_INFO(L"\n%s call report (microseconds)", m_reportName.c_str());
            IMLOG_INFO(L"Call                                       # calls       Min       Max       Avg");
            IMLOG_INFO(L"--------------------------------------------------------------------------------");
            first = false;
        }
        string sMsg = callName + L" " + format(cr.calls) + L" " + format(cr.minInMicroseconds) + L" " + format(cr.maxInMicroseconds) + L" " + format((long)(cr.totalMicroseconds / cr.calls));
        IMLOG_INFO(L"%s", sMsg.c_str());
        ++it;
    }

    if (totalCalls > 0)
        IMLOG_INFO(L"Total                                    %s",format(totalCalls).c_str());

    m_results.clear();
}

string CallReporter::format(LONGLONG number)
{
    wchar_t str[255];
    wnsprintf(str, 255, L"%9lld", number);
    string result(str);
    return result;
}


MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s started", (const wchar_t *)callName);
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s (%s) started", (const wchar_t *)callName, (const wchar_t *)p1);
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName, ConstNormalizedPathPtr path) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s (%s) started", (const wchar_t *)callName, (const wchar_t *)path->GetRelativePath().c_str());
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1, const wchar_t *p2) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s (%s, %s) started", (const wchar_t *)callName, (const wchar_t *)p1, (const wchar_t *)p2);
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName, const wchar_t *p1, ConstNormalizedPathPtr path) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s (%s, %s) started", (const wchar_t *)callName, (const wchar_t *)p1, (const wchar_t *)path->GetRelativePath().c_str());
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::MethodCall(CallReporter& reporter, const wchar_t *callName, ConstNormalizedPathPtr path, ConstNormalizedPathPtr path2) : m_reporter(reporter)
{
    m_callName = callName;
    m_ended = false;
    IMLOG_DEBUG(L"%s (%s, %s) started", (const wchar_t *)callName, (const wchar_t *)path->GetRelativePath().c_str(), (const wchar_t *)path2->GetRelativePath().c_str());
    m_timer.Reset();
    m_timer.Start();
}

MethodCall::~MethodCall()
{
    _End(0, false);
}

void MethodCall::End(NtStatus ret, const wchar_t *revisedCallName)
{
    m_callName = revisedCallName;
    _End((unsigned int)ret, true);
}

void MethodCall::End(ApiRet ret)
{
    _End((unsigned int)ret, true);
}

void MethodCall::_End(unsigned int ret, bool callCompleted)
{
    if (m_ended)
        return;

    m_timer.Stop();
    if (Stopwatch::TicksPerSecond >= 1000000)
    {
        LONGLONG ticksPerMicrosecond = Stopwatch::TicksPerSecond / 1000000;
        m_microseconds = m_timer.ElapsedTicks / ticksPerMicrosecond;
        if (LogMgr::IsDebugEnabled())
        {
            string msg;
            if (callCompleted)
            {
                if (ret == 0)
                    msg = string::Format(L"%s ended in %I64d microsecond(s)", (const wchar_t *)m_callName, (unsigned __int64)m_microseconds);
                else
                    msg = string::Format(L"%s ended in %I64d microsecond(s), err=0x%X", (const wchar_t *)m_callName, (unsigned __int64)m_microseconds, (unsigned int)ret);
            }
            else
                msg = string::Format(L"%s ended in %I64d microsecond(s), err=crash", (const wchar_t *)m_callName, (unsigned __int64)m_microseconds);
            IMLOG_DEBUG(L"%s", msg.c_str());
        }
    }
    else if (Stopwatch::TicksPerSecond >= 1000)
    {
        LONGLONG ticksPerMilliseconds = Stopwatch::TicksPerSecond / 1000;
        LONGLONG ms = m_timer.ElapsedTicks / ticksPerMilliseconds;
        m_microseconds = ms * 1000;
        if (LogMgr::IsDebugEnabled())
        {
            string msg;
            if (callCompleted)
            {
                if (ret == 0)
                    msg = string::Format(L"%s ended in %I64d microsecond(s)", (const wchar_t *)m_callName, (unsigned __int64)ms);
                else
                    msg = string::Format(L"%s ended in %I64d microsecond(s), err=0x%X", (const wchar_t *)m_callName, (unsigned __int64)ms, (unsigned int)ret);
            }
            else
                msg = string::Format(L"%s ended in %I64d microsecond(s), err=crash", (const wchar_t *)m_callName, (unsigned __int64)ms);
            IMLOG_DEBUG(L"%s", msg.c_str());
        }
    }
    else
    {
        // don't bother
        m_microseconds = 0;
    }

    m_ended = true;
    m_reporter.Record(*this);
}
