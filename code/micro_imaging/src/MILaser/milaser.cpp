#include "milaser.h"
#include <QLibrary>

typedef bool(*SetParam)(float pp1, float pp2, float pp3, float pp4, float pc1, float pc2, float pc3, float pc4);
typedef bool(*Connect)(const char* portName);
typedef bool(*Release)(void);
typedef bool(*Activate)(int channel, bool status);
typedef bool(*SetPower)(int channel, float power);
typedef bool(*UpPower)(int channel);
typedef bool(*DownPower)(int channel);

MI_RESULTS MILaserConnect(const char* portName)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    Connect func = (Connect)lib.resolve("LaserLib2_Open");
    SetParam funcB = (SetParam)lib.resolve("LaserLib2_SetParam");

    if(!func | !funcB)
    {
        lib.unload();
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    if(!func(portName))
    {
        lib.unload();
        return API_FAILED_LASER_CONNECT_FAILED;
    }

    if(!funcB(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0))
    {
        lib.unload();
        return API_FAILED_LASER_CONNECT_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserRelease(void)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    Release func = (Release)lib.resolve("LasterLib2_Close");
    if(!func())
    {
        lib.unload();
        return API_FAILED_LASER_RELEASE_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserOpenChannel(LASER_CHAN_ID channelId)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    Activate func = (Activate)lib.resolve("LaserLib2_Active");

    if(!func(channelId + 1, true))
    {
        lib.unload();
        return API_FAILED_LASER_OPEN_CHANNEL_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserCloseChannel(LASER_CHAN_ID channelId)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    Activate func = (Activate)lib.resolve("LaserLib2_Active");

    if(!func(channelId + 1, false))
    {
        lib.unload();
        return API_FAILED_LASER_CLOSE_CHANNEL_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserSetPower(LASER_CHAN_ID channelId, double power)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    SetPower func = (SetPower)lib.resolve("LaserLib2_SetPower");

    if(!func(channelId + 1, power))
    {
        lib.unload();
        return API_FAILED_LASER_SET_POWER_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserUpPower(LASER_CHAN_ID channelId)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    UpPower func = (UpPower)lib.resolve("LaserLib2_UpPower");

    if(!func(channelId + 1))
    {
        lib.unload();
        return API_FAILED_LASER_UP_POWER_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}

MI_RESULTS MILaserDownPower(LASER_CHAN_ID channelId)
{
    QLibrary lib("LaserLib2.dll");
    if(!lib.load())
    {
        return API_FAILED_LASER_LOAD_DLL_FAILED;
    }

    UpPower func = (UpPower)lib.resolve("LaserLib2_DownPower");

    if(!func(channelId + 1))
    {
        lib.unload();
        return API_FAILED_LASER_DOWN_POWER_FAILED;
    }

    lib.unload();
    return API_SUCCESS;
}
