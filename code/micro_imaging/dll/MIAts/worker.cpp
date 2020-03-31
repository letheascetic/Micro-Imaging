#include "worker.h"

ATS_WORKER::ATS_WORKER(QObject *parent):QThread(parent), m_bStopped(false)
{

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

