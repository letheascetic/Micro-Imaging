#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QMutexLocker>

#include "AlazarApi.h"
#include "AlazarCmd.h"
#include "AlazarError.h"

typedef struct _WORKER_STATUS
{
    U32 bytesPerBuffer;
    U32 buffersCompleted;
    U32 bytesTransferred;
    uint16_t* buffer;
}WORKER_STATUS;

class ATS_WORKER : public QThread
{
    Q_OBJECT
public:
    explicit ATS_WORKER(QObject *parent = nullptr);
    ~ATS_WORKER();
    void run();
    void stop();
    void getReady(WORKER_STATUS m_status);

signals:
    void BufferReady(int value);

private:
    bool m_bStopped;
    QMutex m_mutex;
    WORKER_STATUS m_status;
};

typedef ATS_WORKER* PATS_WORKER;

#endif // WORKER_H
