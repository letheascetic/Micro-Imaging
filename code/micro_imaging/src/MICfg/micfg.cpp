#include "micfg.h"

#define CHAN_NUM (4)
#define LASER_CHAN_NUM CHAN_NUM
#define PMT_CHAN_NUM CHAN_NUM

#define LASER_POWER_DEFAULT     (10.0)
#define PMT_GAIN_DEFAULT        (10.0)
#define CRS_AMPLITUDE_DEFAULT   (3.3)
#define SCAN_POINTS_DEFAULT     (1024)

typedef struct _LASER_CHAN {
    LASER_CHAN_ID id;
    LASER_CHAN_SWITCH status;
    double power;
} LASER_CHANNELS[LASER_CHAN_NUM];

typedef struct _PMT {
    double gain;
} PMT_CHANNELS[PMT_CHAN_NUM];

typedef struct _CRS {
    double Amplitude;
} CRS;

typedef struct _SCAN {
    SCAN_MODE Mode;
    SCAN_STRATEGY Strategy;
    SCAN_POINTS X;
    SCAN_POINTS Y;
    SCAN_FLAG Flag;
} SCAN;


struct _MI_CFG
{
    LASER_CHANNELS LaserChannels;
    PMT_CHANNELS PmtChannels;
    CRS mCRS;
    SCAN mSCAN;

    _MI_CFG();
    void Init();
};

typedef struct _MI_CFG MICfg, *PMICfg;

MICfg m_MICfg;
CONFIG pMIcfg = &m_MICfg;

void LaserInit(CONFIG pConfig);
void PMTInit(CONFIG pConfig);
void CRSInit(CONFIG pConfig);
void ScanInit(CONFIG pConfig);


CONFIG MICfgGetConfiguration()
{
    Test();
    return pMIcfg;
}

uint32_t MICfgGetChannelNum(void)
{
    return CHAN_NUM;
}

MI_RESULTS MICfgLaserSetSwitch(CONFIG pConfig, LASER_CHAN_ID id, LASER_CHAN_SWITCH status)
{
    ((PMICfg)pConfig)->LaserChannels[id].status = status;
    return API_SUCCESS;
}

MI_RESULTS MICfgLaserSetPower(CONFIG pConfig, LASER_CHAN_ID id, double gain)
{
    ((PMICfg)pConfig)->LaserChannels[id].power = gain;
    return API_SUCCESS;
}

LASER_CHAN_SWITCH MICfgLaserGetSwitch(CONFIG pConfig, LASER_CHAN_ID id)
{
    return ((PMICfg)pConfig)->LaserChannels[id].status;
}

MI_RESULTS MICfgPMTSetGain(CONFIG pConfig, PMT_CHAN_ID id, double gain)
{
    ((PMICfg)pConfig)->PmtChannels[id].gain = gain;
    return API_SUCCESS;
}

double MICfgPMTGetGain(CONFIG pConfig, PMT_CHAN_ID id)
{
    return ((PMICfg)pConfig)->PmtChannels[id].gain;
}

MI_RESULTS MICfgCRSSetAmplitude(CONFIG pConfig, double amplitude)
{
    ((PMICfg)pConfig)->mCRS.Amplitude = amplitude;
    return API_SUCCESS;
}

double MICfgCRSGetAmplitude(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mCRS.Amplitude;
}

MI_RESULTS MICfgSetScanMode(CONFIG pConfig, SCAN_MODE mode)
{
    ((PMICfg)pConfig)->mSCAN.Mode = mode;
    return API_SUCCESS;
}

MI_RESULTS MICfgSetScanStartegy(CONFIG pConfig, SCAN_STRATEGY startegy)
{
    ((PMICfg)pConfig)->mSCAN.Strategy = startegy;
    return API_SUCCESS;
}

MI_RESULTS MICfgSetScanPointsX(CONFIG pConfig, SCAN_POINTS x)
{
    ((PMICfg)pConfig)->mSCAN.X = x;
    return API_SUCCESS;
}

MI_RESULTS MICfgSetScanPointsY(CONFIG pConfig, SCAN_POINTS y)
{
    ((PMICfg)pConfig)->mSCAN.Y = y;
    return API_SUCCESS;
}

MI_RESULTS MICfgSetScanFlag(CONFIG pConfig, SCAN_FLAG flag)
{
    ((PMICfg)pConfig)->mSCAN.Flag = flag;
    return API_SUCCESS;
}

SCAN_MODE MICfgGetSacnMode(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mSCAN.Mode;
}

SCAN_STRATEGY MICfgGetScanStartegy(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mSCAN.Strategy;
}

SCAN_POINTS MICfgGetScanPointsX(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mSCAN.X;
}

SCAN_POINTS MICfgGetScanPointsY(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mSCAN.Y;
}

SCAN_FLAG MICfgGetScanFlag(CONFIG pConfig)
{
    return ((PMICfg)pConfig)->mSCAN.Flag;
}

_MI_CFG::_MI_CFG()
{
    Init();
}

void _MI_CFG::Init()
{
    for(int i=0; i<LASER_CHAN_NUM; i++)
    {
        LaserChannels[i].id = i;
        LaserChannels[i].status = LASER_CHAN_SWITCH_ON;
        LaserChannels[i].power = LASER_POWER_DEFAULT;
    }

    for(int i=0; i<PMT_CHAN_NUM; i++)
    {
        PmtChannels[i].gain = PMT_GAIN_DEFAULT;
    }

    mCRS.Amplitude = CRS_AMPLITUDE_DEFAULT;

    mSCAN.Mode = SCAN_MODE_GALVANOMETER;
    mSCAN.Strategy = SCAN_STRATEGY_Z_UNIDIRECTION;
    mSCAN.X = SCAN_POINTS_DEFAULT;
    mSCAN.Y = SCAN_POINTS_DEFAULT;
    mSCAN.Flag = 0;

}




