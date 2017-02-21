#ifndef NetworkTaskStructDefine_h__
#define NetworkTaskStructDefine_h__

#include <QString>
#include <QVariant>
#include "NetworkTaskMacros.h"

namespace NetworkTask
{
    //任务参数基类
	struct stNetworkParamBase
	{
		stNetworkParamBase()
		{
			taskPriority = NetworkTask::Normal;
		}

		//任务类型
		virtual int  taskType() const  { return -1; }

		//是否有效
		virtual bool isValid() const = 0;

		NetworkTask::ETaskPriority				taskPriority;  //任务优先级
	};

	//任务信息
	struct stNetworkTaskInfo
	{
		stNetworkTaskInfo();

		stNetworkTaskInfo(int type);

		stNetworkTaskInfo(const QString& taskID, int type);

		const int					taskType;			//任务类型
		const QString		taskID;				//任务ID
	};


	//网络返回结果
	struct stNetworkResult
	{
		stNetworkResult()
		{
			errorCode = NetworkTask::NoError;
			success = false;
		}

		stNetworkResult(bool suc, EReturnCode code)
		{
			errorCode = code;
			success = suc;
		}

		bool success;												//成功
		QVariant data;												//数据
		int	errorCode;							//失败后的错误代码
		QString message;										//错误消息
	};

	//下载任务参数
	struct stDownloadParam : public stNetworkParamBase
	{
		stDownloadParam()
		{
			taskPriority = NetworkTask::Low;
		}
		//任务类型
		virtual int taskType()  const { return NetworkTask::TaskType_Donwload; }

		//是否有效
		virtual bool isValid() const{ return (!downloadUrl.isEmpty()); }

		QString downloadUrl;				//下载的地址
	};
}

Q_DECLARE_METATYPE(NetworkTask::stNetworkResult);
Q_DECLARE_METATYPE(NetworkTask::stNetworkTaskInfo);
#endif // NetworkTaskStructDefine_h__
