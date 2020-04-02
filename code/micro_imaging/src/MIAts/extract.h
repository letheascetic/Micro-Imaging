#ifndef EXTRACT_H
#define EXTRACT_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QMutexLocker>

#include "AlazarApi.h"
#include "AlazarCmd.h"
#include "AlazarError.h"

class _MI_ATS;

typedef _MI_ATS MIAts, *PMIAts;

typedef struct _WORKER_STATUS
{
    U32 bytesPerBuffer;
    U32 buffersCompleted;
    U32 bytesTransferred;
    uint16_t* buffer;
}WORKER_STATUS;

class EXTRACTOR : public QThread
{
    Q_OBJECT
public:
    EXTRACTOR(PMIAts pAts);
    ~EXTRACTOR();
    void run();
    void stop();
    void getReady(WORKER_STATUS m_status);
    void getBuffer();

signals:
    void BufferReady(int value);

private:
    bool m_bStopped;
    QMutex m_mutex;
    PMIAts m_pAts;
    //WORKER_STATUS m_status;
};

typedef EXTRACTOR* PATS_WORKER;

#endif // WORKER_H
