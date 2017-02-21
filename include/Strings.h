#ifndef Strings_h__
#define Strings_h__

#include <QtCore>

namespace NetworkTaskLib
{
	const QString kHttpErrorCode = QObject::tr("http error code", "NetworkTaskLib");
	const QString kNoError = QObject::tr("no error", "NetworkTaskLib");
	const QString kUnknownError = QObject::tr("unknown error", "NetworkTaskLib");
	const QString kInvalidParameter = QObject::tr("invalid parameter", "NetworkTaskLib");
	const QString kTimeOut = QObject::tr("time out", "NetworkTaskLib");
	const QString kEmptyData = QObject::tr("empty data", "NetworkTaskLib");
}															

#endif // Strings_h__
