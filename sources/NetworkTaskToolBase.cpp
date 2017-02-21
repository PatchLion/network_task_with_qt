#include "stdafx.h"
#include "NetworkTaskToolBase.h"
#include <QObject>
#include "NetworkTaskMacros.h"
#include "Strings.h"

QString CNetworkTaskToolBase::errorDescription(int errorCode)
{
	if (errorCode > 0)
	{
		return NetworkTaskLib::kHttpErrorCode + ": " + QString::number(errorCode);
	}

	switch (errorCode)
	{
	case NetworkTask::NoError:				return NetworkTaskLib::kNoError;
	case NetworkTask::InvalidParam:		return NetworkTaskLib::kInvalidParameter;
	case NetworkTask::TimeOut:				return NetworkTaskLib::kTimeOut;
	case NetworkTask::EmptyData:				return NetworkTaskLib::kEmptyData;
	}

	return NetworkTaskLib::kUnknownError;
}
