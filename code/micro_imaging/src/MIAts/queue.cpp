#include "queue.h"

ATS_QUEUE::ATS_QUEUE()
{
    m_elemSize = 0;
    m_Initialized = false;
}

ATS_QUEUE::~ATS_QUEUE()
{
    ReleaseQueue();
}

void ATS_QUEUE::InitQueue(uint32_t eSize, uint32_t qSize)
{
    ReleaseQueue();

    m_elemSize = eSize;
    uint16_t* buffer = NULL;
    while(m_unusedQueue.size() < (int)qSize)
    {
        buffer = (uint16_t*)malloc(m_elemSize);
        if(buffer != NULL)
        {
            m_unusedQueue.enqueue(buffer);
        }
    }
}

void ATS_QUEUE::ReleaseQueue()
{
    m_unusedQueue.clear();
    m_usedQueue.clear();
    m_Initialized = false;
    m_elemSize = 0;
}

bool ATS_QUEUE::Initialized()
{
    return m_Initialized;
}

uint32_t ATS_QUEUE::UsedSize()
{
    return m_usedQueue.size();
}

uint32_t ATS_QUEUE::UnusedSize()
{
    return m_unusedQueue.size();
}

uint16_t* ATS_QUEUE::NextUnused()
{
    if(m_unusedQueue.isEmpty())
    {
        m_unusedQueue.enqueue(m_usedQueue.dequeue());
    }
    return m_unusedQueue.head();
}

uint16_t* ATS_QUEUE::LastUsed()
{
    if(m_usedQueue.isEmpty())
    {
        return NULL;
    }
    return m_usedQueue.last();
}

uint32_t ATS_QUEUE::ElementSize()
{
    return m_elemSize;
}

uint16_t* ATS_QUEUE::Dequeue()
{
    if(m_unusedQueue.isEmpty())
    {
        return m_usedQueue.dequeue();
    }
    return m_unusedQueue.dequeue();
}

void ATS_QUEUE::Enqueue(uint16_t* element)
{
    m_usedQueue.enqueue(element);
}

