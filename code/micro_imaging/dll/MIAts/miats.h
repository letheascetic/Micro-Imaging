#ifndef MIATS_H
#define MIATS_H

#include "ats.h"

EXPORT ATS MIAtsOpen(void);
EXPORT void MIAtsClose(void);
EXPORT MI_RESULTS MIAtsGetInfo(ATS pAts, PATS_INFO pAtsInfo);
EXPORT MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig);

#endif // MIATS_H
