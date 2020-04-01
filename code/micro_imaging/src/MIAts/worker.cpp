#include "worker.h"
#include "inc/AlazarApi.h"
#include "inc/AlazarCmd.h"
#include "inc/AlazarError.h"

ATS_WORKER::ATS_WORKER(QObject *parent):QThread(parent), m_bStopped(false)
{
    m_status.buffer = NULL;
}

ATS_WORKER::~ATS_WORKER()
{
    stop();
    quit();
    wait();
}

void ATS_WORKER::run()
{
    int nValue = 10;
    while (nValue--)
    {
        msleep(3000);

        emit BufferReady(nValue);

        QMutexLocker lock(&m_mutex);
        if(m_bStopped)
            break;
    }
}

void ATS_WORKER::stop()
{
    QMutexLocker locker(&m_mutex);
    m_bStopped = true;
}

void ATS_WORKER::getReady(WORKER_STATUS m_status)
{
    this->m_status = m_status;
}

