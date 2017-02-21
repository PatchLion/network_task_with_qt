#include "TestMainWidget.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QFile>
#include "NetworkTaskBase.h"

CTestMainWidget::CTestMainWidget(QWidget* parent /*= 0*/)
	: QWidget(parent)
{

	setupUi(this);
	

	CNetworkTaskBase::setNetworkManagerInstance(&m_networkAccessManager);

	connect(&m_taskManager, &CNetworkTaskManager::taskFinished, this, &CTestMainWidget::onTaskFinished);
	connect(&m_taskManager, &CNetworkTaskManager::taskUploadProgress, this, &CTestMainWidget::onTaskUploadProgress);
	connect(&m_taskManager, &CNetworkTaskManager::taskDownloadProgress, this, &CTestMainWidget::onTaskDownloadProgress);
}

void CTestMainWidget::onTaskUploadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress)
{
	progressBarUpload->setValue(100.0*progress);
}

void CTestMainWidget::onTaskDownloadProgress(const NetworkTask::stNetworkTaskInfo& taskInfo, double progress)
{
	progressBarDownload->setValue(100.0*progress);
}

void CTestMainWidget::onTaskFinished(const NetworkTask::stNetworkTaskInfo& taskInfo, const NetworkTask::stNetworkResult& result)
{
	//QMessageBox::information(this, result.success ? "success" : "failed", QString("task %1 finished").arg(taskInfo.taskID));

	if (result.success)
	{
		const QString savePath = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0] + "/download_image.jpg";

		QFile file(savePath);
		if (file.open(QIODevice::WriteOnly))
		{
			file.write(result.data.toByteArray());
			QMessageBox::information(this, "success", "save file to desktop!");
		}
		else
		{
			QMessageBox::information(this, "failed", "failed to save file to desktop!");
		}
	}
}

void CTestMainWidget::on_pushButtonStartDonwload_clicked(bool checked)
{
	NetworkTask::stDownloadParam param;
	param.downloadUrl = "http://g.hiphotos.baidu.com/image/pic/item/e1fe9925bc315c60ea22e4898eb1cb1349547725.jpg";
	m_taskManager.addTask(param);
}
