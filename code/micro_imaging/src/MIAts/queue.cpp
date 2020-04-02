#include "queue.h"

template<class T>
ATS_QUEUE<T>::ATS_QUEUE()
{
    m_Initialized = false;
}

template<class T>
ATS_QUEUE<T>::~ATS_QUEUE()
{
    ReleaseQueue();
}

template<class T>
void ATS_QUEUE<T>::InitQueue(uint32_t eSize, uint32_t qSize)
{
    ReleaseQueue();

    m_elemSize = eSize;
    uint16_t* buffer = NULL;
    while(m_unusedQueue.size() < qSize)
    {
        buffer = (uint16_t*)malloc(m_elemSize);
        if(buffer != NULL)
        {
            m_unusedQueue.enqueue(buffer);
        }
    }
}

template<class T>
void ATS_QUEUE<T>::ReleaseQueue()
{
    m_unusedQueue.clear();
    m_usedQueue.clear();
    m_Initialized = false;
    m_buffSize = 0;
}

template<class T>
bool ATS_QUEUE<T>::Initialized()
{
    return m_Initialized;
}

template<class T>
uint32_t ATS_QUEUE<T>::UsedSize()
{
    return m_usedQueue.size();
}

template<class T>
uint32_t ATS_QUEUE<T>::UnusedSize()
{
    return m_unusedQueue.size();
}

template<class T>
T ATS_QUEUE<T>::NextUnused()
{
    if(m_unusedQueue.isEmpty())
    {
        m_unusedQueue.enqueue(m_usedQueue.dequeue());
    }
    return m_unusedQueue.head();
}

template<class T>
T ATS_QUEUE<T>::LastUsed()
{
    if(m_usedQueue.isEmpty())
    {
        return NULL;
    }
    return m_usedQueue.last();
}

template<class T>
uint32_t ATS_QUEUE<T>::ElementSize()
{
    return m_elemSize;
}

template<class T>
T ATS_QUEUE<T>::Dequeue()
{
    if(m_unusedQueue.isEmpty())
    {
        return m_usedQueue.dequeue();
    }
    return m_unusedQueue.dequeue();
}

template<class T>
void ATS_QUEUE<T>::Enqueue(T element)
{
    m_usedQueue.enqueue(element);
}

