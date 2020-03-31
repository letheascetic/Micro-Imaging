#ifndef MICFG_H
#define MICFG_H

#include <QtCore/qglobal.h>

#include "midef.h"

typedef uint16_t LASER_CHAN_ID;
typedef uint16_t LASER_CHAN_SWITCH;

#define LASER_CHAN_ID_405_NM 0x0000
#define LASER_CHAN_ID_488_NM 0x0001
#define LASER_CHAN_ID_561_NM 0x0002
#define LASER_CHAN_ID_640_NM 0x0003

#define LASER_CHAN_SWITCH_OFF 0x0000
#define LASER_CHAN_SWITCH_ON  0x0001

typedef LASER_CHAN_ID PMT_CHAN_ID;

typedef uint16_t SCAN_MODE;
typedef uint16_t SCAN_STRATEGY;
typedef uint16_t SCAN_FLAG;
typedef uint16_t SCAN_POINTS;

#define SCAN_MODE_RESONANT 0x0000
#define SCAN_MODE_GALVANOMETER 0x0001

#define SCAN_STRATEGY_Z_BIDIRECTION 0x0000
#define SCAN_STRATEGY_Z_UNIDIRECTION 0x0001
#define SCAN_STRATEGY_CIRCLE_EQUI_ANGULAR 0x0002
#define SCAN_STRATEGY_Z_EQUI_LINEAR 0x0003

#define COSINE_DISTORTION_CORRECTION 0x0001

typedef void* CONFIG;

CONFIG MICfgGetConfiguration(void);
//void MICfgFreeConfiguration(void);

uint32_t MICfgGetChannelNum(void);

MI_RESULTS MICfgLaserSetSwitch(CONFIG pConfig, LASER_CHAN_ID id, LASER_CHAN_SWITCH status);
MI_RESULTS MICfgLaserSetPower(CONFIG pConfig, LASER_CHAN_ID id, double power);
LASER_CHAN_SWITCH MICfgLaserGetSwitch(CONFIG pConfig, LASER_CHAN_ID id);
double MICfgLaserGetPower(CONFIG pConfig, LASER_CHAN_ID id);

MI_RESULTS MICfgPMTSetGain(CONFIG pConfig, PMT_CHAN_ID id, double gain);
double MICfgPMTGetGain(CONFIG pConfig, PMT_CHAN_ID id);

MI_RESULTS MICfgCRSSetAmplitude(CONFIG pConfig, double amplitude);
double MICfgCRSGetAmplitude(CONFIG pConfig);

MI_RESULTS MICfgSetScanMode(CONFIG pConfig, SCAN_MODE mode);
MI_RESULTS MICfgSetScanStartegy(CONFIG pConfig, SCAN_STRATEGY startegy);
MI_RESULTS MICfgSetScanPointsX(CONFIG pConfig, SCAN_POINTS x);
MI_RESULTS MICfgSetScanPointsY(CONFIG pConfig, SCAN_POINTS y);
MI_RESULTS MICfgSetScanFlag(CONFIG pConfig, SCAN_FLAG flag);
SCAN_MODE MICfgGetSacnMode(CONFIG pConfig);
SCAN_STRATEGY MICfgGetScanStartegy(CONFIG pConfig);
SCAN_POINTS MICfgGetScanPointsX(CONFIG pConfig);
SCAN_POINTS MICfgGetScanPointsY(CONFIG pConfig);
SCAN_FLAG MICfgGetScanFlag(CONFIG pConfig);


#endif // MICFG_H
