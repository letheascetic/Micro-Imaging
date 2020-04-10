#ifndef ATS_QUEUE_H
#define ATS_QUEUE_H

#include <QQueue>
#define QUEUE_SIZE_DEFAULT 31

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
    uint16_t* NextUnused(void);
    uint16_t* LastUsed(void);
    uint16_t* Dequeue(void);
    void Enqueue(uint16_t*);

private:
    bool m_Initialized;
    uint32_t m_elemSize;        // bytes per element
    QQueue<uint16_t*> m_unusedQueue;
    QQueue<uint16_t*> m_usedQueue;
};

#endif // ATS_QUEUE_H
