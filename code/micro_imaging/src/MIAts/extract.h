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
}WORKER_STATUS;

class EXTRACT : public QThread
{
    Q_OBJECT
public:
    EXTRACT(PMIAts pAts);
    ~EXTRACT();
    void run();
    void stop();
    bool isRunning();

private:
    void extract();

signals:
    void BufferExtracted();

private:
    bool m_bRunning;
    QMutex m_mutex;
    PMIAts m_pAts;
};

typedef EXTRACT* PEXTRACT;

#endif // WORKER_H
