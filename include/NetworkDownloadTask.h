//下载网络任务
#ifndef NetworkDownloadTask_h__
#define NetworkDownloadTask_h__

#include "NetworkTaskBase.h"
#include "NetworkTaskStructs.h"

class CNetworkDownloadTask : public CNetworkTaskBase
{
	Q_OBJECT

public: 
	CNetworkDownloadTask(const NetworkTask::stDownloadParam& param, QObject* parent = 0);
	CNetworkDownloadTask(const NetworkTask::stDownloadParam& param, const QString& taskID, QObject* parent = 0);
	
public:
	//开始任务
	virtual bool startTask();

private Q_SLOTS:
	void onReplyFinished();

private:
	const NetworkTask::stDownloadParam	m_param;
};
#endif // NetworkDownloadTask_h__
