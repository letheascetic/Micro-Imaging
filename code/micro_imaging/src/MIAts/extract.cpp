#include "extract.h"

EXTRACT::EXTRACT(PMIAts pAts): m_bStopped(false)
{
    m_pAts = pAts;
    //m_status.buffer = NULL;
}

EXTRACT::~EXTRACT()
{
    stop();
    quit();
    wait();
}

void EXTRACT::run()
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

void EXTRACT::stop()
{
    QMutexLocker locker(&m_mutex);
    m_bStopped = true;
}

void EXTRACT::getReady(WORKER_STATUS m_status)
{
    //this->m_status = m_status;
}

void EXTRACT::getBuffer()
{
    RETURN_CODE code = ApiSuccess;
    //m_pAts
    //code = AlazarWaitNextAsyncBufferComplete()



}
