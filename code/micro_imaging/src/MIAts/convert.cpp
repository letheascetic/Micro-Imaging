#include "convert.h"
#include "miats.h"

CONVERT::CONVERT(PMIAts pAts)
{
    m_pAts = pAts;
}


void CONVERT::convert()
{
    QThread::msleep(2000);
    qDebug() << "[convert]: buffer converted...";
    emit BufferConverted();
}

void CONVERT::BufferToConvert()
{
    qDebug() << "[convert]: buffer to convert...";
    convert();
}


