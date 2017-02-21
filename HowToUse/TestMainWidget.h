#ifndef TestMainWidget_h__
#define TestMainWidget_h__

#include <QWidget>
#include <QNetworkAccessManager>
#include "ui_TestMainWidget.h"
#include "NetworkTaskManager.h"

class CTestMainWidget : public QWidget, public Ui_TestMainWidget
{
	Q_OBJECT
public:
	CTestMainWidget(QWidget* parent = 0);


protected Q_SLOTS:
	void onTaskUploadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void onTaskDownloadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress);
	void onTaskFinished(const NetworkTask::stNetworkTaskInfo& taskInfo, const NetworkTask::stNetworkResult& result);
	void on_pushButtonStartDonwload_clicked(bool checked);

private:
	QNetworkAccessManager m_networkAccessManager;
	CNetworkTaskManager m_taskManager;
};

#endif // TestMainWidget_h__
