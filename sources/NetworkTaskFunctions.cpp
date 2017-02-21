#include "stdafx.h"
#include "NetworkTaskFunctions.h"
#include <QSslConfiguration>
#include "Version.h"

void NetworkTask::createSSLRequest(QNetworkRequest& request, const QUrl& url)
{
	request.setUrl(url);

	QSslConfiguration sslConfig = request.sslConfiguration();
	sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
	sslConfig.setProtocol(QSsl::AnyProtocol);

	request.setSslConfiguration(sslConfig);
}

QNetworkRequest NetworkTask::createSSLRequest(const QString& strUrl)
{
	QNetworkRequest request;

	createSSLRequest(request, QUrl(strUrl));

	return request;
}

QString NetworkTask::version()
{
	return NetworkTaskLib::kVersion;
}
