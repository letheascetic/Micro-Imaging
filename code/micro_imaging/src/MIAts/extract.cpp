#include "extract.h"
#include "miats.h"

EXTRACT::EXTRACT(PMIAts pAts): m_bStopped(false)
{
    m_pAts = pAts;
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

void EXTRACT::extract()
{
    RETURN_CODE code = ApiSuccess;
    uint16_t* buffer = NULL;

    while(!m_bStopped)
    {
        buffer = m_pAts->m_buffers.NextUnused();
        code = AlazarWaitNextAsyncBufferComplete(m_pAts->handle, buffer, m_pAts->m_buffers.ElementSize(), 1000);
        if(code == ApiSuccess || code == ApiTransferComplete)  // new buffer achieved
        {
            buffer = m_pAts->m_buffers.Dequeue();
            m_pAts->m_buffers.Enqueue(buffer);
            emit BufferReceived();
        }
        else if(code == ApiWaitTimeout)
        {
            // To do: log timeout event
        }
        else
        {
            // To do: log this error
        }
    }
}
