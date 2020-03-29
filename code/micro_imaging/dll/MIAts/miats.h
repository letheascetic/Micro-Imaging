#ifndef MIATS_H
#define MIATS_H

#include "midef.h"
#include "micfg.h"
#include "MIAts_global.h"

typedef void* ATS;

ATS MIAtsOpen(void);
void MIAtsClose(void);

MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig);

#endif // MIATS_H
