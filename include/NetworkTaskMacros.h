#ifndef NetworkTaskMacros_h__
#define NetworkTaskMacros_h__

namespace NetworkTask
{
	//Priority 优先级
	enum ETaskPriority
	{
		High,				
		Normal,			
		Low,			
	};

	//Status 任务状态
	enum ETaskStatus
	{
		Ready,				
		Processing,		
		Processed,		
	};

	//Code 返回码
	enum EReturnCode
	{
		//>0 is http error
		NoError = 0,
		Unknown = -100000,
		InvalidParam,
		TimeOut,
		EmptyData,

		ErrorCode_UserDefine = -50000
	};

	//网络任务类型
	enum ETaskType
	{
		TaskType_Donwload,

		TaskType_UserDefine,
	};
}
#endif // NetworkTaskMacros_h__
