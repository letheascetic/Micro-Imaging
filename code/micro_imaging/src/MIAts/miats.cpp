#include "miats.h"

#define ALAZAR_BOARD_SYSTEM_ID 0x01
#define ALAZAR_BOARD_ID        0x01

ATS pMIats = NULL;

_MI_ATS::_MI_ATS(HANDLE handle)
{
    this->handle = handle;
    this->buffer = NULL;
    this->worker = new EXTRACTOR(this);
}

_MI_ATS::~_MI_ATS()
{
    handle = NULL;
    if(worker != NULL)
    {
        delete worker;
    }
    worker = NULL;
    if(buffer != NULL)
    {
        delete buffer;
    }
    buffer = NULL;
}

ATS MIAtsOpen(void)
{
    if(pMIats == NULL)
    {
        HANDLE handle = AlazarGetBoardBySystemID(ALAZAR_BOARD_SYSTEM_ID, ALAZAR_BOARD_ID);
        if(handle)
        {
            PMIAts pATS = new MIAts(handle);
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

    PMIAts ats = (PMIAts)pAts;
    RETURN_CODE code = ApiSuccess;

    // define pre-trigger-samples/post-trigger-samples
    SCAN_POINTS x = MICfgGetScanPointsX(pConfig);
    SCAN_POINTS y = MICfgGetScanPointsY(pConfig);
    uint32_t preTriggerSamples = 0;
    uint32_t postTriggerSamples = x;    // samples per record
    uint32_t recordsPerBuffer = y;      // records per buffer
    U32 recordsPerAcquisition = 0x7FFFFFFF;
    //U32 buffersPerAcquisition = recordsPerAcquisition / recordsPerBuffer;

    // get activated channel mask / activated channel num
    uint32_t channelMask = 0;
    uint32_t activatedChannelNum = 0;
    for(int i=0; i < (int)MICfgGetChannelNum(); i++)
    {
        if(MICfgLaserGetSwitch(pConfig, i) == LASER_CHAN_SWITCH_ON)
        {
            activatedChannelNum++;
            channelMask |= (1U << i);
        }
    }
    if(activatedChannelNum == 3)        // 3 channel not supported for ATS9440
    {
        activatedChannelNum = 4;
        channelMask |= 0x0F;
    }

    // get the sample size in bits, and the on-board memory size in samples per channel
    U8 bitsPerSample;
    U32 maxSamplesPerChannel;
    code = AlazarGetChannelInfo(ats->handle, &maxSamplesPerChannel, &bitsPerSample);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_GET_CHANNEL_INFO_FAILED;
    }

    // calculate the size of each DMA buffer in bytes
    U32 bytesPerSample = (bitsPerSample + 7) / 8;
    U32 samplesPerRecord = preTriggerSamples + postTriggerSamples;
    U32 bytesPerRecord = bytesPerSample * samplesPerRecord;
    U32 bytesPerBuffer = bytesPerRecord * recordsPerBuffer * activatedChannelNum;

    // allocate memory for DMA buffers
    ats->buffer = (uint16_t*)malloc(bytesPerBuffer);
    if(ats->buffer == NULL)
    {
        return API_FAILED_ATS_MALLOC_BUFFER_FAILED;
    }

    // config ats record size
    code = AlazarSetRecordSize(ats->handle, preTriggerSamples, postTriggerSamples);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_SET_RECORD_SIZE_FAILED;
    }

    // config the ats borad to make an NPT AUTODMA acquisition
    U32 flag = ADMA_NPT | ADMA_ALLOC_BUFFERS | ADMA_EXTERNAL_STARTCAPTURE;
    code = AlazarBeforeAsyncRead(ats->handle,
                                 channelMask,
                                 -(long)preTriggerSamples,
                                 samplesPerRecord,
                                 recordsPerBuffer,
                                 recordsPerAcquisition,
                                 flag);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_CONFIG_ASYNC_READ_FAILED;
    }

    // for resonant scan mode, enable CRS is needed
    if(MICfgGetSacnMode(pConfig) == SCAN_MODE_RESONANT)
    {
        code = AlazarConfigureAuxIO(ats->handle, AUX_OUT_SERIAL_DATA, 1);
        if(code != ApiSuccess)
        {
            return API_FAILED_ATS_ENABLE_CRS_FAILED;
        }
    }

    code = AlazarStartCapture(ats->handle);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_START_CAPTURE_FAILED;
    }

    code = AlazarForceTriggerEnable(ats->handle);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_FORCE_TRIGGER_ENABLE_FAILED;
    }

    WORKER_STATUS w_status;
    w_status.buffer = ats->buffer;
    w_status.bytesPerBuffer = bytesPerBuffer;
    w_status.buffersCompleted = 0;
    w_status.bytesTransferred = 0;

    ats->worker->getReady(w_status);
    ats->worker->start();

    return API_SUCCESS;
}

MI_RESULTS MIAtsStop(ATS pAts)
{
    if(pAts == NULL)
    {
        return API_FAILED_ATS_HANDLE_INVALID;
    }

    PMIAts ats = (PMIAts)pAts;
    RETURN_CODE code = ApiSuccess;

    code = AlazarAbortAsyncRead(ats->handle);
    if(code != ApiSuccess)
    {
        return API_FAILED_ATS_ABORT_ASYNC_READ_FAILED;
    }

    ats->worker->stop();
    free(ats->buffer);
    ats->buffer = NULL;

    return API_SUCCESS;
}






