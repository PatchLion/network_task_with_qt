#ifndef NetworkTaskManager_h__
#define NetworkTaskManager_h__

#include <QMap>
#include "NetworkTaskStructs.h"

class QTimer;
class CNetworkTaskBase;
class CNetworkTaskManager : public QObject
{
	Q_OBJECT
private:
	typedef QMap< NetworkTask::ETaskPriority, QList<CNetworkTaskBase*> >  MapPriorityToTaskList;

public:
	CNetworkTaskManager(QObject* parent = 0);
	virtual ~CNetworkTaskManager();

public:
	//添加任务
	QString addTask(const NetworkTask::stDownloadParam& param, const QString& taskID = "");

protected:
	QString addTaskMap(CNetworkTaskBase* task);

protected:
	bool checkTaskExist(const QString& taskID) const;

	void checkTaskPriority(const NetworkTask::stNetworkParamBase* param, const QString& taskID);

private:
	CNetworkTaskBase* findTaskByTaskID(const QString& id);

	int processingTask(NetworkTask::ETaskPriority priority) const;

Q_SIGNALS:
	void taskUploadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskDownloadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void taskFinished(const NetworkTask::stNetworkTaskInfo& taskInfo, const NetworkTask::stNetworkResult& result);

private Q_SLOTS:
	void onStartTaskTimer();

private:
	QList<CNetworkTaskBase*>			m_listAllTask;
	QList<CNetworkTaskBase*>			m_listHighPriority;			//高优先级队列
	QList<CNetworkTaskBase*>			m_listNormalPriority;		//正常优先级队列
	QList<CNetworkTaskBase*>			m_listLowPriority;			//低优先级队列
   QTimer												*m_startTaskTimer;
};

#endif // NetworkTaskManager_h__
