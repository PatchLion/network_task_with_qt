#include "stdafx.h"
#include "NetworkTaskManager.h"
#include "NetworkTaskBase.h"
#include <QDebug>
#include <QTimer>
#include "NetworkDownloadTask.h"

const int kStartTimerInterval = 50;		
const int kNormalCount = 25;		
const int kLowCount = 2;		

CNetworkTaskManager::CNetworkTaskManager(QObject* parent)
	: QObject(parent)
    , m_startTaskTimer(0)
{
	m_startTaskTimer = new QTimer(this);
	m_startTaskTimer->setInterval(kStartTimerInterval);
	m_startTaskTimer->setSingleShot(false);
	m_startTaskTimer->start();

	connect(m_startTaskTimer, &QTimer::timeout, this, &CNetworkTaskManager::onStartTaskTimer);
}
CNetworkTaskManager::~CNetworkTaskManager()
{

}

bool CNetworkTaskManager::checkTaskExist(const QString& taskID) const
{
	if (!taskID.isEmpty())
	{
		for (int i = 0; i < m_listAllTask.size(); i++)
		{
			if (m_listAllTask[i]->taskInfo().taskID == taskID)
			{
				if (m_listAllTask[i]->isRemoved())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}

void CNetworkTaskManager::checkTaskPriority(const NetworkTask::stNetworkParamBase* param, const QString& taskID)
{
	if (param && !taskID.isEmpty())
	{
		CNetworkTaskBase* taskBase = 0;
		for (int i = 0; i < m_listAllTask.size(); i++)
		{
			if (m_listAllTask[i]->taskInfo().taskID == taskID)
			{
				taskBase = m_listAllTask[i];
			}
		}
	
		if (taskBase)
		{
			if (taskBase->taskState() == NetworkTask::Processed)
			{
				Q_EMIT taskFinished(taskBase->taskInfo(), taskBase->taskResult());
			}
			else
			{
				if (param->taskPriority == NetworkTask::High
					&& taskBase->priority() != NetworkTask::High)
				{
					taskBase->startTask();
				}
			}
		}
	}
}

QString CNetworkTaskManager::addTaskMap(CNetworkTaskBase* task)
{
	Q_ASSERT(task);

	QList<CNetworkTaskBase*>::iterator taskItor = qFind(m_listAllTask.begin(), m_listAllTask.end(), task);
	if (m_listAllTask.end() == taskItor)
	{
		connect(task, &CNetworkTaskBase::taskUploadProgress, this, &CNetworkTaskManager::taskUploadProgress, Qt::QueuedConnection);
		connect(task, &CNetworkTaskBase::taskDownloadProgress, this, &CNetworkTaskManager::taskDownloadProgress, Qt::QueuedConnection);
		connect(task, &CNetworkTaskBase::taskFinished, this, &CNetworkTaskManager::taskFinished, Qt::QueuedConnection);

		m_listAllTask.push_back(task);

		switch (task->priority())
		{
		case NetworkTask::High:
		{
			m_listHighPriority.push_back(task);
		}
			break;
		case NetworkTask::Normal:
		{
			m_listNormalPriority.push_back(task);
		}
			break;
		case NetworkTask::Low:
		{
			m_listLowPriority .push_back(task);
		}
			break;
		}
	}

	return task->taskInfo().taskID;
}

void CNetworkTaskManager::onStartTaskTimer()
{
	Q_FOREACH(CNetworkTaskBase* task, m_listHighPriority)
	{
		if (task)
		{
			task->startTask();
		}
	}

	m_listHighPriority.clear();

	while (!m_listNormalPriority.isEmpty() && processingTask(NetworkTask::Normal) < kNormalCount)
	{
		CNetworkTaskBase* task = m_listNormalPriority[0];
		if (task && task->taskState() == NetworkTask::Ready)
		{
			task->startTask();
		}
		m_listNormalPriority.pop_front();
	}
	
	while (!m_listLowPriority.isEmpty() && processingTask(NetworkTask::Low) < kLowCount)
	{
		CNetworkTaskBase* task = m_listLowPriority[0];
		if (task&& task->taskState() == NetworkTask::Ready)
		{
			task->startTask();
		}
		m_listLowPriority.pop_front();
	}
}

int CNetworkTaskManager::processingTask(NetworkTask::ETaskPriority priority) const
{
	int i = 0;
	Q_FOREACH(CNetworkTaskBase* task, m_listAllTask)
	{
		if (task->priority() == priority 
			&& task->taskState() == NetworkTask::Processing)
		{ 
			i++;
		}
	}

	return i;
}

QString CNetworkTaskManager::addTask(const NetworkTask::stDownloadParam& param, const QString& taskID /*= ""*/)
{
	if (checkTaskExist(taskID))
	{
		checkTaskPriority(&param, taskID);
		return taskID;
	}

	return addTaskMap(new CNetworkDownloadTask(param, taskID));
}
