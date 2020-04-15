#ifndef MILASER_H
#define MILASER_H

#include "midef.h"
#include "micfg.h"

MI_RESULTS MILaserConnect(const char* portName);
MI_RESULTS MILaserRelease(void);
MI_RESULTS MILaserOpenChannel(LASER_CHAN_ID channelId);
MI_RESULTS MILaserCloseChannel(LASER_CHAN_ID channelId);
MI_RESULTS MILaserSetPower(LASER_CHAN_ID channelId, double power);
MI_RESULTS MILaserUpPower(LASER_CHAN_ID channelId);
MI_RESULTS MILaserDownPower(LASER_CHAN_ID channelId);

#endif // MILASER_H
