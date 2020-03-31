#ifndef MIATS_H
#define MIATS_H

#include "ats.h"

ATS MIAtsOpen(void);
void MIAtsClose(void);
MI_RESULTS MIAtsGetInfo(ATS pAts, PATS_INFO pAtsInfo);
MI_RESULTS MIAtsSetConfiguration(ATS pAts, CONFIG pConfig);

#endif // MIATS_H
