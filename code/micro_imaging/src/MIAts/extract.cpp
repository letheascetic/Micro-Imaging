#include "extract.h"

EXTRACTOR::EXTRACTOR(PMIAts pAts): m_bStopped(false)
{
    m_pAts = pAts;
    //m_status.buffer = NULL;
}

EXTRACTOR::~EXTRACTOR()
{
    stop();
    quit();
    wait();
}

void EXTRACTOR::run()
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

void EXTRACTOR::stop()
{
    QMutexLocker locker(&m_mutex);
    m_bStopped = true;
}

void EXTRACTOR::getReady(WORKER_STATUS m_status)
{
    //this->m_status = m_status;
}

void EXTRACTOR::getBuffer()
{
    RETURN_CODE code = ApiSuccess;
    //m_pAts
    //code = AlazarWaitNextAsyncBufferComplete()



}
