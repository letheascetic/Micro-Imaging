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
void ATS_QUEUE<T>::InitQueue(uint32_t bytes, uint32_t size)
{
    ReleaseQueue();

    for(int i=0; i<(int)size; i++)
    {
        uint16_t* buffer = (uint16_t*)malloc(bytes);
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

