#include "miats.h"

#include "AlazarApi.h"
#include "AlazarCmd.h"
#include "AlazarError.h"

#define ALAZAR_BOARD_SYSTEM_ID 0x01
#define ALAZAR_BOARD_ID        0x01

struct _MI_ATS
{
    HANDLE handle = NULL;
};

typedef struct _MI_ATS MIAts, *PMIAts;

ATS pMIats = NULL;

ATS MIAtsOpen(void)
{
    if(pMIats == NULL)
    {
        HANDLE handle = AlazarGetBoardBySystemID(ALAZAR_BOARD_SYSTEM_ID, ALAZAR_BOARD_ID);
        if(handle)
        {
            PMIAts pATS = new MIAts();
            pATS->handle = handle;
            pMIats = pATS;
        }
    }
    return pMIats;
}

void MIAtsClose()
{
    if(pMIats)
    {
        delete (PMIAts)pMIats;
        pMIats = NULL;
    }
}

MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig)
{


}

