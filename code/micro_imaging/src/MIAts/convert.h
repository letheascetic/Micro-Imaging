#ifndef CONVERT_H
#define CONVERT_H

#include <QThread>

class _MI_ATS;
typedef _MI_ATS MIAts, *PMIAts;

class CONVERT : public QThread
{
    Q_OBJECT
public:
    CONVERT(PMIAts pAts);

private:
    PMIAts m_pAts;
};

#endif // CONVERT_H
