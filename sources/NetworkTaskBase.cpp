#include "stdafx.h"
#include "NetworkTaskBase.h"
#include "ThreadTimer.h"
#include "NetworkTaskFunctions.h"
#include <QNetworkAccessManager>

const int kTimeOutInterval = 15000;   //超时时间(毫秒)

namespace NetworkTask
{
	CNetworkTaskToolBase  g_toolbase;
	CNetworkTaskToolBase* g_tool = 0;
	QNetworkAccessManager* g_accessManager = 0;
}

void CNetworkTaskBase::setNetworkManagerInstance(QNetworkAccessManager* manager)
{
	NetworkTask::g_accessManager = manager;
}

QNetworkAccessManager* CNetworkTaskBase::networkManagerInstance()
{
	return NetworkTask::g_accessManager;
}
void CNetworkTaskBase::setTool(CNetworkTaskToolBase* toolBase)
{
	NetworkTask::g_tool = toolBase;
}

CNetworkTaskToolBase* CNetworkTaskBase::tool()
{
	if (!NetworkTask::g_tool)
	{
		return &NetworkTask::g_toolbase;
	}

	return NetworkTask::g_tool;
}

CNetworkTaskBase::CNetworkTaskBase(int type, const NetworkTask::stNetworkParamBase* param, QObject* parent)
	: QObject(parent)
	, m_info(type)
	, m_reply(0)
	, m_taskPriority(NetworkTask::Normal)
	, m_taskState(NetworkTask::Ready)
	, m_timeOutTimer(0)
	, m_isRemoved(false)
{
	if (param)
	{
		m_taskPriority = param->taskPriority;
	}

	connect(this, &CNetworkTaskBase::startTimerSignal, this, &CNetworkTaskBase::startTimeoutTimer, Qt::QueuedConnection);
}

CNetworkTaskBase::CNetworkTaskBase(const QString& taskID, int type, const  NetworkTask::stNetworkParamBase* param, QObject* parent)
	: QObject(parent)
	, m_info(taskID, type)
	, m_reply(0)
	, m_taskPriority(NetworkTask::Normal)
	, m_taskState(NetworkTask::Ready)
	, m_timeOutTimer(0)
	, m_isRemoved(false)
{
	if (param)
	{
		m_taskPriority = param->taskPriority;
	}

	connect(this, &CNetworkTaskBase::startTimerSignal, this, &CNetworkTaskBase::startTimeoutTimer, Qt::QueuedConnection);
}

const NetworkTask::stNetworkResult& CNetworkTaskBase::taskResult() const
{
	return m_result;
}

const NetworkTask::stNetworkTaskInfo& CNetworkTaskBase::taskInfo() const
{
	return m_info;
}

void CNetworkTaskBase::setCurrentReply(QNetworkReply* reply)
{
	if (m_reply)
	{
		disconnect(m_reply, &QNetworkReply::finished, this, &CNetworkTaskBase::onReplyFinished);
		disconnect(m_reply, &QNetworkReply::uploadProgress, this, &CNetworkTaskBase::onUploadProgress);
		disconnect(m_reply, &QNetworkReply::downloadProgress, this, &CNetworkTaskBase::onDownloadProgress);
	}

	if (reply)
	{
		m_reply = reply;
		connect(reply, &QNetworkReply::finished, this, &CNetworkTaskBase::onReplyFinished);
		connect(reply, &QNetworkReply::uploadProgress, this, &CNetworkTaskBase::onUploadProgress);
		connect(reply, &QNetworkReply::downloadProgress, this, &CNetworkTaskBase::onDownloadProgress);
	}
}

void CNetworkTaskBase::endTask()
{
	if (currentReply() && currentReply()->isRunning())
	{
		currentReply()->abort();
	}

	stopTimeoutTimer();
}

bool CNetworkTaskBase::checkParam(const NetworkTask::stNetworkParamBase* param)
{
	if (!param || !param->isValid())
	{
		m_result.success = false;
		m_result.errorCode = NetworkTask::InvalidParam;
		m_result.message = tool()->errorDescription(NetworkTask::InvalidParam);

		AFTER_TASK_FINISHED();

		return false;
	}
	return true;
}

bool CNetworkTaskBase::resolveWhenHttpError(QNetworkReply::NetworkError httpCode)
{
	if (QNetworkReply::NoError == httpCode)
	{
		return true;
	}

	m_result.success = false;
	m_result.errorCode = httpCode;
	m_result.message = tool()->errorDescription(httpCode);

	AFTER_TASK_FINISHED();

	return false;
}

void CNetworkTaskBase::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	resetTimeoutTimer();
	TASK_DOWNLOAD_PROGRESS((double)bytesReceived / (double)bytesTotal);
}

void CNetworkTaskBase::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
 {
	TASK_UPLOAD_PROGRESS((double)bytesSent / (double)bytesTotal);
}

void CNetworkTaskBase::setTaskState(NetworkTask::ETaskStatus state)
{
	m_taskState = state;
}


void CNetworkTaskBase::resetTimeoutTimer()
{
	if (m_timeOutTimer)
	{
	}
}

void CNetworkTaskBase::startTimeoutTimer()
{
	if (!m_timeOutTimer)
	{
		m_timeOutTimer = new CThreadTimer;
		connect(m_timeOutTimer, &CThreadTimer::timeout, this, &CNetworkTaskBase::onTimeOut, Qt::QueuedConnection);
		m_timeOutTimer->setInterval(kTimeOutInterval);
		m_timeOutTimer->setSingleShot(true);
	}

	if (m_timeOutTimer)
	{
		if (m_timeOutTimer->isRunning())
		{
			m_timeOutTimer->quit();
		}

		m_timeOutTimer->start();
	}
}

void CNetworkTaskBase::stopTimeoutTimer()
{
	if (m_timeOutTimer)
	{
		m_timeOutTimer->quit();
	}
}

void CNetworkTaskBase::onTimeOut()
{
	//超时
	setTimeOut(true);
	stopTimeoutTimer();

	m_result.success = false;
	m_result.errorCode = NetworkTask::TimeOut;
	m_result.message = tool()->errorDescription(NetworkTask::TimeOut);

	AFTER_TASK_FINISHED();
}

void CNetworkTaskBase::onReplyFinished()
{
	stopTimeoutTimer();
}

bool CNetworkTaskBase::startTask()
{
	setTimeOut(false);
	setTaskState(NetworkTask::Processing);
	Q_EMIT startTimerSignal();
	return true;
}

CNetworkTaskBase::~CNetworkTaskBase()
{
	m_reply = 0;
	if (m_timeOutTimer)
	{
		if (m_timeOutTimer->isRunning())
		{
			m_timeOutTimer->quit();
			m_timeOutTimer->wait();
		}
		delete m_timeOutTimer;
		m_timeOutTimer = 0;
	}
}

