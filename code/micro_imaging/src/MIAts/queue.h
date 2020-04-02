#ifndef QUEUE_H
#define QUEUE_H

#include <QQueue>

#define QUEUE_SIZE_DEFAULT 16

template<class T>
class ATS_QUEUE
{
public:
    ATS_QUEUE();
    ~ATS_QUEUE();
    void InitQueue(uint32_t bytes, uint32_t size = QUEUE_SIZE_DEFAULT);
    void ReleaseQueue();
    bool Initialized();
    uint32_t UsedSize();
    uint32_t UnusedSize();

private:
    bool m_Initialized;
    QQueue<T> m_unusedQueue;
    QQueue<T> m_usedQueue;

};


#endif // QUEUE_H
