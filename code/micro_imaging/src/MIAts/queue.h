#ifndef ATS_QUEUE_H
#define AST_QUEUE_H

#include <QQueue>
#define QUEUE_SIZE_DEFAULT 16

template<class T>
class ATS_QUEUE
{
public:
    ATS_QUEUE();
    ~ATS_QUEUE();
    void InitQueue(uint32_t bSize, uint32_t qSize = QUEUE_SIZE_DEFAULT);
    void ReleaseQueue(void);
    bool Initialized(void);
    uint32_t UsedSize(void);
    uint32_t UnusedSize(void);
    uint32_t ElementSize(void);
    T NextUnused(void);
    T LastUsed(void);
    T Dequeue(void);
    void Enqueue(T);

private:
    bool m_Initialized;
    uint32_t m_elemSize;        // bytes per element
    QQueue<T> m_unusedQueue;
    QQueue<T> m_usedQueue;
};


#endif // ATS_QUEUE_H
