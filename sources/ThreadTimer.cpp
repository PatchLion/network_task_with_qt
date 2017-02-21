#include "stdafx.h"
#include "ThreadTimer.h"

const int kUnitInterval = 1;

CThreadTimer::CThreadTimer(QObject* parent /*= 0*/)
	: QThread(parent)
	, m_timerCount(0)
	, m_isSingleShot(true)
	, m_interval(1000)
	, m_isQuit(false)
{

}

void CThreadTimer::run()
{
	m_timerCount = 0;

	while (true)
	{
		if (isQuit())
		{
			return;
		}
			
		msleep(kUnitInterval);
		m_timerCount += kUnitInterval;

		if (interval() == m_timerCount)
		{
			Q_EMIT timeout();
			m_timerCount = 0;

			if (isSingleShot())
			{
				break;
			}
		}
	}
}

void CThreadTimer::quit()
{
	m_isQuit = true;
	QThread::quit();
}

void CThreadTimer::restart()
{
	m_timerCount = 0;
}
