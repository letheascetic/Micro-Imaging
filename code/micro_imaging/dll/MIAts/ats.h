#ifndef ATS_H
#define ATS_H

#include <QObject>

#include "midef.h"
#include "worker.h"
#include "inc/AlazarApi.h"
#include "inc/AlazarCmd.h"
#include "inc/AlazarError.h"
#include "../../lib/MICfg/micfg.h"

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
    _MI_ATS();
    ~_MI_ATS();

public:
    HANDLE handle;
    uint16_t* buffer;
    ATS_WORKER *worker;

private:
    //ATS_WORKER worker;

signals:
    void BufferReceived();

};

typedef _MI_ATS MIAts, *PMIAts;

ATS MIAtsOpen(void);
void MIAtsClose(void);
MI_RESULTS MIAtsGetInfo(ATS pAts, PATS_INFO pAtsInfo);
MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig);

#endif // ATS_H
