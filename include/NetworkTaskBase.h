#ifndef NetworkTaskBase_h__
#define NetworkTaskBase_h__

#include <QNetworkReply>
#include "NetworkTaskStructs.h"
#include "NetworkTaskToolBase.h"

class CThreadTimer;
class CNetworkTaskToolBase;
class QNetworkAccessManager;
class CNetworkTaskBase : public QObject
{
	Q_OBJECT
	friend class CNetworkTaskManager;

public:
	CNetworkTaskBase(int type, const NetworkTask::stNetworkParamBase* param, QObject* parent = 0);
	CNetworkTaskBase(const QString& taskID, int type, const NetworkTask::stNetworkParamBase* param, QObject* parent = 0);
	virtual ~CNetworkTaskBase();

public:
	//任务状态
	NetworkTask::ETaskStatus taskState() const{ return m_taskState; }

	//任务信息
	const NetworkTask::stNetworkTaskInfo& taskInfo() const;

	//任务结果
	const NetworkTask::stNetworkResult& taskResult() const;

	//开始任务
	virtual bool startTask();

	//终止任务
	virtual void endTask();

	//设置Tool实例
	static void setTool(CNetworkTaskToolBase* toolBase);
	static CNetworkTaskToolBase* tool();

	//设置网络访问对象
	static void setNetworkManagerInstance(QNetworkAccessManager* manager);
	static QNetworkAccessManager* networkManagerInstance();
	
	//任务优先级
	NetworkTask::ETaskPriority priority() const { return m_taskPriority; }
	void setPriority(NetworkTask::ETaskPriority priority) { m_taskPriority = priority; }

	//设置移除标志
	void setRemoveFlag() { m_isRemoved = true; }
	bool isRemoved() const { return m_isRemoved; }

signals:
	//void invalidToken();

protected:
	//解析http返回错误
	virtual bool resolveWhenHttpError(QNetworkReply::NetworkError httpCode);

	//检测参数
	virtual bool checkParam(const NetworkTask::stNetworkParamBase* param);

protected:
	//网络结果
	NetworkTask::stNetworkResult& taskResult() { return m_result; }
	
	//响应对象
	QNetworkReply* currentReply() { return m_reply; }
	void setCurrentReply(QNetworkReply* reply);

	//设置任务状态
	void setTaskState(NetworkTask::ETaskStatus state);

	//是否已超时
	bool isTimeOut() const{ return m_isTimeOut; }
	void setTimeOut(bool timeout) { m_isTimeOut = timeout; }

protected Q_SLOTS :
	virtual void onReplyFinished();
	virtual void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
	virtual void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	virtual void onTimeOut();

	//超时定时器
	void startTimeoutTimer();
	void resetTimeoutTimer();
	void stopTimeoutTimer();

Q_SIGNALS:
	void taskUploadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskDownloadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskFinished(const NetworkTask::stNetworkTaskInfo& taskInfo, const NetworkTask::stNetworkResult& result);

private:
Q_SIGNALS:
	//私有信号
	void startTimerSignal();

private:
	bool m_isRemoved;			//是否被移除
	NetworkTask::ETaskStatus m_taskState;				//任务状态
	NetworkTask::stNetworkTaskInfo	m_info;							//任务信息
	NetworkTask::stNetworkResult m_result;						//任务结果
	NetworkTask::ETaskPriority m_taskPriority;				//任务优先级
	CThreadTimer *m_timeOutTimer;		//任务超时定时器

	QNetworkReply *m_reply;
	bool m_isTimeOut;
};

//内部宏
#define AFTER_TASK_FINISHED() { setTaskState(NetworkTask::Processed); Q_EMIT taskFinished(taskInfo(), taskResult()); }	
#define TASK_UPLOAD_PROGRESS(progress) (Q_EMIT taskUploadProgress(taskInfo(), progress))
#define TASK_DOWNLOAD_PROGRESS(progress) (Q_EMIT taskDownloadProgress(taskInfo(), progress))

#endif // NetworkTaskBase_h__
