#pragma once
#include <QThread>
#include<QtCore/QDebug>



class ProgressBarThread: public QThread {
	Q_OBJECT
public slots:
	void setTotal(int value) {
		this->total = value;
	}
signals:
	// マインスレッド終わる同時にサブスレッドも終わらせる

	// QObject::connect(Thread, SIGNAL(finished()), Application, SLOT(quit()))
	 //スレッドの変化をプロバーへ送る
	 //QObject::connect(Thread, SIGNAL(progress()), Window, SLOT(onProgress()))
	void progress(int value);
private:
	int total = 100;
	void run() {
		qDebug() << this->objectName();
		int value;
		for (int i = 0; i < total; i++) {
			
			value = (i % total);
			emit progress(value);
			QThread::msleep(1);
		}
		emit progress(total);

	}
};
