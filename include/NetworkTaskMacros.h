#ifndef NetworkTaskMacros_h__
#define NetworkTaskMacros_h__

namespace NetworkTask
{
	//Priority ���ȼ�
	enum ETaskPriority
	{
		High,				
		Normal,			
		Low,			
	};

	//Status ����״̬
	enum ETaskStatus
	{
		Ready,				
		Processing,		
		Processed,		
	};

	//Code ������
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

	//������������
	enum ETaskType
	{
		TaskType_Donwload,

		TaskType_UserDefine,
	};
}
#endif // NetworkTaskMacros_h__
