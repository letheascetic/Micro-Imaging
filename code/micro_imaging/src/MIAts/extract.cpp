#include "extract.h"
#include "miats.h"

EXTRACT::EXTRACT(PMIAts pAts): m_bRunning(false)
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
    extract();
}

void EXTRACT::stop()
{
    QMutexLocker locker(&m_mutex);
    m_bRunning = false;
}

void EXTRACT::extract()
{
    RETURN_CODE code = ApiSuccess;
    uint16_t* buffer = NULL;

    while(m_bRunning)
    {
        buffer = m_pAts->m_buffers.NextUnused();
        code = AlazarWaitNextAsyncBufferComplete(m_pAts->handle, buffer, m_pAts->m_buffers.ElementSize(), 1000);
        if(code == ApiSuccess || code == ApiTransferComplete)  // new buffer achieved
        {
            buffer = m_pAts->m_buffers.Dequeue();
            m_pAts->m_buffers.Enqueue(buffer);
            emit BufferExtracted();
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
//    m_bRunning = true;
//    while (m_bRunning)
//    {
//        msleep(3000);
//        qDebug() << "[extract]: buffer extracted...";
//        emit BufferExtracted();
//    }
}

bool EXTRACT::isRunning()
{
    return m_bRunning;
}
