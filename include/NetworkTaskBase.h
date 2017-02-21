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
	//����״̬
	NetworkTask::ETaskStatus taskState() const{ return m_taskState; }

	//������Ϣ
	const NetworkTask::stNetworkTaskInfo& taskInfo() const;

	//������
	const NetworkTask::stNetworkResult& taskResult() const;

	//��ʼ����
	virtual bool startTask();

	//��ֹ����
	virtual void endTask();

	//����Toolʵ��
	static void setTool(CNetworkTaskToolBase* toolBase);
	static CNetworkTaskToolBase* tool();

	//����������ʶ���
	static void setNetworkManagerInstance(QNetworkAccessManager* manager);
	static QNetworkAccessManager* networkManagerInstance();
	
	//�������ȼ�
	NetworkTask::ETaskPriority priority() const { return m_taskPriority; }
	void setPriority(NetworkTask::ETaskPriority priority) { m_taskPriority = priority; }

	//�����Ƴ���־
	void setRemoveFlag() { m_isRemoved = true; }
	bool isRemoved() const { return m_isRemoved; }

signals:
	//void invalidToken();

protected:
	//����http���ش���
	virtual bool resolveWhenHttpError(QNetworkReply::NetworkError httpCode);

	//������
	virtual bool checkParam(const NetworkTask::stNetworkParamBase* param);

protected:
	//������
	NetworkTask::stNetworkResult& taskResult() { return m_result; }
	
	//��Ӧ����
	QNetworkReply* currentReply() { return m_reply; }
	void setCurrentReply(QNetworkReply* reply);

	//��������״̬
	void setTaskState(NetworkTask::ETaskStatus state);

	//�Ƿ��ѳ�ʱ
	bool isTimeOut() const{ return m_isTimeOut; }
	void setTimeOut(bool timeout) { m_isTimeOut = timeout; }

protected Q_SLOTS :
	virtual void onReplyFinished();
	virtual void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
	virtual void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	virtual void onTimeOut();

	//��ʱ��ʱ��
	void startTimeoutTimer();
	void resetTimeoutTimer();
	void stopTimeoutTimer();

Q_SIGNALS:
	void taskUploadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskDownloadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskFinished(const NetworkTask::stNetworkTaskInfo& taskInfo, const NetworkTask::stNetworkResult& result);

private:
Q_SIGNALS:
	//˽���ź�
	void startTimerSignal();

private:
	bool m_isRemoved;			//�Ƿ��Ƴ�
	NetworkTask::ETaskStatus m_taskState;				//����״̬
	NetworkTask::stNetworkTaskInfo	m_info;							//������Ϣ
	NetworkTask::stNetworkResult m_result;						//������
	NetworkTask::ETaskPriority m_taskPriority;				//�������ȼ�
	CThreadTimer *m_timeOutTimer;		//����ʱ��ʱ��

	QNetworkReply *m_reply;
	bool m_isTimeOut;
};

//�ڲ���
#define AFTER_TASK_FINISHED() { setTaskState(NetworkTask::Processed); Q_EMIT taskFinished(taskInfo(), taskResult()); }	
#define TASK_UPLOAD_PROGRESS(progress) (Q_EMIT taskUploadProgress(taskInfo(), progress))
#define TASK_DOWNLOAD_PROGRESS(progress) (Q_EMIT taskDownloadProgress(taskInfo(), progress))

#endif // NetworkTaskBase_h__
