#ifndef CONVERT_H
#define CONVERT_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QMutexLocker>

class _MI_ATS;
typedef _MI_ATS MIAts, *PMIAts;

class CONVERT : public QObject
{
    Q_OBJECT
public:
    CONVERT(PMIAts pAts);
private:
    void convert();

signals:
    void BufferConverted();

public slots:
    void BufferToConvert();

private:
    PMIAts m_pAts;
};

typedef CONVERT* PCONVERT;

#endif // CONVERT_H
