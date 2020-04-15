#include "milaser.h"
#include <QLibrary>

typedef bool(*SetParam)(float pp1, float pp2, float pp3, float pp4, float pc1, float pc2, float pc3, float pc4);
typedef bool(*Connect)(const char* portName);
typedef bool(*Release)(void);
typedef bool(*Active)(int channel, bool status);
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
