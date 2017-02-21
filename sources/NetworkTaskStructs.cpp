#include "stdafx.h"
#include "NetworkTaskStructs.h"
#include <QUuid>
#include "NetworkTaskFunctions.h"

NetworkTask::stNetworkTaskInfo::stNetworkTaskInfo()
	: taskID(QUuid::createUuid().toString())
	, taskType(-1){}

NetworkTask::stNetworkTaskInfo::stNetworkTaskInfo(int type)
	: taskID(QUuid::createUuid().toString())
	, taskType(type){}

NetworkTask::stNetworkTaskInfo::stNetworkTaskInfo(const QString& taskID, int type)
	: taskID(taskID.isEmpty() ? QUuid::createUuid().toString() : taskID)
	, taskType(type){}
