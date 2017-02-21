#ifndef NetworkTaskToolBase_h__
#define NetworkTaskToolBase_h__

#include <QtCore/QString>

class CNetworkTaskToolBase
{
public:
	//error description
	virtual QString errorDescription(int errorCode);
};

#endif // NetworkTaskToolBase_h__
