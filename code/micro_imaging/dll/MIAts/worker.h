#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QMutexLocker>

class ATS_WORKER : public QThread
{
    Q_OBJECT
public:
    explicit ATS_WORKER(QObject *parent = nullptr);
    ~ATS_WORKER();
    void run();
    void stop();

signals:
    void BufferReady(int value);

private:
    bool m_bStopped;
    QMutex m_mutex;
};

#endif // WORKER_H
