#ifndef MIATS_H
#define MIATS_H

#include <QtCore/qglobal.h>

#include "midef.h"
#include "micfg.h"
#include "queue.h"
#include "extract.h"

typedef void* ATS;

typedef struct _ATS_INFO {
    uint32_t BOARD_MODEL;             // board model
    uint8_t BOARD_MAJOR_NUMBER;       // board version
    uint8_t BOARD_MINOR_NUMBER;
    uint8_t SDK_MAJOR_NUMBER;         // sdk version
    uint8_t SDK_MINOR_NUMBER;
    uint8_t SDK_REVISION;
    uint8_t DRIVER_MAJOR_NUMBER;      // driver version
    uint8_t DRIVER_MINOR_NUMBER;
    uint8_t DRIVER_REVISION;
    uint8_t CPLD_MAJOR_NUMBER;        // CPLD version
    uint8_t CPLD_MINOR_NUMBER;
} ATS_INFO, *PATS_INFO;

class _MI_ATS: public QObject
{
    Q_OBJECT

public:
    _MI_ATS(HANDLE handle);
    ~_MI_ATS();

public:
    HANDLE handle;          // handle for ats device
    ATS_QUEUE<uint16_t*>  m_bufQueue;
    EXTRACTOR *worker;     // pointer to work thread
    uint16_t* buffer;     // to do: ring buffers is better

private:
    //bool m_bRunning;

signals:
    //void BufferReceived();

};



ATS MIAtsOpen(void);
void MIAtsClose(void);
MI_RESULTS MIAtsGetInfo(ATS pAts, PATS_INFO pAtsInfo);
MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig);
MI_RESULTS MIAtsStart(ATS pAts, CONFIG pConfig);
MI_RESULTS MIAtsStop(ATS pAts);

#endif // MIATS_H
