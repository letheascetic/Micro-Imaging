#include "ats.h"
#include "AlazarApi.h"

#define ALAZAR_BOARD_SYSTEM_ID 0x01
#define ALAZAR_BOARD_ID        0x01

ATS pMIats = NULL;

_MI_ATS::_MI_ATS()
{
    handle = NULL;
    worker = NULL;
}

_MI_ATS::~_MI_ATS()
{
    handle = NULL;
    if(worker != NULL)
    {
        delete worker;
    }
    worker = NULL;
}

ATS MIAtsOpen(void)
{
    if(pMIats == NULL)
    {
        HANDLE handle = AlazarGetBoardBySystemID(ALAZAR_BOARD_SYSTEM_ID, ALAZAR_BOARD_ID);
        if(handle)
        {
            PMIAts pATS = new MIAts();
            pATS->handle = handle;
            pATS->worker = new ATS_WORKER();
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

MI_RESULTS MIAtsGetInfo(ATS pAts, PATS_INFO pAtsInfo)
{
    if(pAts == NULL)
    {
        return API_FAILED_ATS_HANDLE_INVALID;
    }

    if(pAtsInfo == NULL)
    {
        return API_FAILED_ATS_INFO_INSTANCE_INVALID;
    }

    HANDLE handle = ((PMIAts)pAts)->handle;
    RETURN_CODE code = ApiSuccess;

    // get board model
    pAtsInfo->BOARD_MODEL = AlazarGetBoardKind(handle);

    // get board version
    code = AlazarGetBoardRevision(handle, &pAtsInfo->BOARD_MAJOR_NUMBER, &pAtsInfo->BOARD_MINOR_NUMBER);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_GET_BOARD_VERSION_FAILED;
    }

    // get sdk version
    code = AlazarGetSDKVersion(&pAtsInfo->SDK_MAJOR_NUMBER, &pAtsInfo->SDK_MINOR_NUMBER, &pAtsInfo->SDK_REVISION);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_GET_SDK_VERSION_FAILED;
    }

    // get driver version
    code = AlazarGetDriverVersion(&pAtsInfo->DRIVER_MAJOR_NUMBER, &pAtsInfo->DRIVER_MINOR_NUMBER, &pAtsInfo->DRIVER_REVISION);
    if(code != ApiSuccess)
    {
        return API_FIALED_ATS_GET_DRIVER_VERSION_FAILED;
    }

    // get cpld version
    code = AlazarGetCPLDVersion(handle, &pAtsInfo->CPLD_MAJOR_NUMBER, &pAtsInfo->CPLD_MINOR_NUMBER);
    if(code != ApiSuccess)
    {
        return API_FIALED_ATS_GET_CPLD_VERSION_FAILED;
    }

    return API_SUCCESS;
}

MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig)
{
    if(pAts == NULL)
    {
        return API_FAILED_ATS_HANDLE_INVALID;
    }

    if(pConfig == NULL)
    {
        return API_FAILED_CONFIG_HANDLE_INVALID;
    }

    HANDLE handle = ((PMIAts)pAts)->handle;
    RETURN_CODE code = ApiSuccess;

    // set clock: internal_clock, sample_rate, clock_edge
    code = AlazarSetCaptureClock(handle, INTERNAL_CLOCK, SAMPLE_RATE_10MSPS, CLOCK_EDGE_RISING, 0);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_CLOCK_FAILED;
    }

    // config input channel: gain, coupling, termination, input_range
    code = AlazarInputControlEx(handle, CHANNEL_A, DC_COUPLING, INPUT_RANGE_PM_4_V, IMPEDANCE_50_OHM);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_INPUT_CHANNEL_FAILED;
    }
    code = AlazarInputControlEx(handle, CHANNEL_B, DC_COUPLING, INPUT_RANGE_PM_4_V, IMPEDANCE_50_OHM);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_INPUT_CHANNEL_FAILED;
    }
    code = AlazarInputControlEx(handle, CHANNEL_C, DC_COUPLING, INPUT_RANGE_PM_4_V, IMPEDANCE_50_OHM);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_INPUT_CHANNEL_FAILED;
    }
    code = AlazarInputControlEx(handle, CHANNEL_D, DC_COUPLING, INPUT_RANGE_PM_4_V, IMPEDANCE_50_OHM);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_INPUT_CHANNEL_FAILED;
    }

    // set trigger operation
    double trigger_range_volts = 5.0;
    double trigger_level_volts = 2.0;
    uint32_t trigger_level = (uint32_t)(128 + 127 * trigger_level_volts / trigger_range_volts);
    code = AlazarSetTriggerOperation(handle,
                              TRIG_ENGINE_OP_J,            // use trigger engine J
                              TRIG_ENGINE_J,
                              TRIG_EXTERNAL,               // use external trigger
                              TRIGGER_SLOPE_POSITIVE,      // rising edge
                              trigger_level,               // trigger level 2.0v
                              TRIG_ENGINE_K,               // disable trigger engine K
                              TRIG_DISABLE,
                              TRIGGER_SLOPE_POSITIVE,
                              128);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_TRIGGER_OPERATION_FAILED;
    }

    // set external trigger
    code = AlazarSetExternalTrigger(handle, DC_COUPLING, ETR_5V);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_EXTERNAL_TRIGGER_FAILED;
    }

    // set trigger timeout to zero wait forever for trigger events
    code = AlazarSetTriggerTimeOut(handle, 0);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_TRIGGER_TIMEOUT_FAILED;
    }

    // set trigger delay
    code = AlazarSetTriggerDelay(handle, 0);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_TRIGGER_DELAY_FAILED;
    }

    // set AUX I/O
    // For ATS9440, config AUX I/O 2 as a digital output
    code = AlazarConfigureAuxIO(handle, AUX_OUT_SERIAL_DATA, 0);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_AUX_IO_FAILED;
    }

    return API_SUCCESS;
}

MI_RESULTS MIAtsStart(ATS pAts, CONFIG pConfig)
{
    if(pAts == NULL)
    {
        return API_FAILED_ATS_HANDLE_INVALID;
    }

    if(pConfig == NULL)
    {
        return API_FAILED_CONFIG_HANDLE_INVALID;
    }

    HANDLE handle = ((PMIAts)pAts)->handle;
    PATS_WORKER worker = ((PMIAts)pAts)->worker;

    // define pre-trigger-samples/post-trigger-samples
    uint32_t preTriggerSamples = 0;


    return API_SUCCESS;
}
