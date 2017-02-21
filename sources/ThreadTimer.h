#ifndef ThreadTimer_h__
#define ThreadTimer_h__

#include <QThread>

class CThreadTimer : public QThread
{
    Q_OBJECT
public:
	explicit CThreadTimer(QObject* parent = 0);
	~CThreadTimer(){}

public:
	//interval
	void setInterval(int msec) { m_interval = msec; }
	int interval() const { return m_interval; }

	//single shot flag
	void setSingleShot(bool singleShot) { m_isSingleShot = singleShot; }
	bool isSingleShot() const { return m_isSingleShot; }

	//
	void restart();

public Q_SLOTS:
	void quit();

protected:
    void run();

private:
	bool isQuit() const { return m_isQuit; }

Q_SIGNALS:
	void timeout();

private:
	int			m_timerCount;					//
	bool		m_isSingleShot;				//
	int           m_interval;							//
	bool		m_isQuit;
};
#endif // ThreadTimer_h__
