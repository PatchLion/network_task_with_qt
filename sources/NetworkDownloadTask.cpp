#include "NetworkDownloadTask.h"
#include "NetworkTaskFunctions.h"
//#include "TestNetworkTaskMacroDefine.h"

CNetworkDownloadTask::CNetworkDownloadTask(const NetworkTask::stDownloadParam& param, QObject* parent)
	: CNetworkTaskBase(param.taskType(), &param, parent)
	, m_param(param)
{

}

CNetworkDownloadTask::CNetworkDownloadTask(const NetworkTask::stDownloadParam& param, const QString& taskID, QObject* parent)
	: CNetworkTaskBase(taskID, param.taskType(), &param, parent)
	, m_param(param)
{

}

bool CNetworkDownloadTask::startTask()
{
	Q_ASSERT(!currentReply());
	Q_ASSERT(CNetworkTaskBase::networkManagerInstance());

	if (!checkParam(&m_param))
	{
		return false;
	}

	CNetworkTaskBase::startTask();

	const bool isHttps = (QUrl(m_param.downloadUrl).scheme().toLower() == "https");

	QNetworkRequest request;

	if (isHttps)
	{
		NetworkTask::createSSLRequest(request, m_param.downloadUrl);
	}
	else
	{
		request.setUrl(m_param.downloadUrl);
	}

	setCurrentReply(CNetworkTaskBase::networkManagerInstance()->get(request));

	return true;
}

void CNetworkDownloadTask::onReplyFinished()
{
	Q_ASSERT(currentReply());

	CNetworkTaskBase::onReplyFinished();
	if (isTimeOut())
	{
		return;
	}
	QNetworkReply::NetworkError httpCode = currentReply()->error();

	if (QNetworkReply::NoError != httpCode)
	{
		resolveWhenHttpError(httpCode);
		return;
	}

	const QByteArray result = currentReply()->readAll();
	if (result.isEmpty())
	{
		taskResult().success = false;
		taskResult().errorCode = NetworkTask::EmptyData;
		taskResult().message = tool()->errorDescription(NetworkTask::EmptyData);
	}
	else
	{
		taskResult().success = true;
		taskResult().data = result;
	}

	AFTER_TASK_FINISHED();
}