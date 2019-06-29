#ifndef _KUN__SCANSERIALTIMER_H_
#define _KUN__SCANSERIALTIMER_H_

#include <QTimer>
#include <QThread>
#include "interface.h"

class ScanSerialTimer : QThread
{
    Q_OBJECT
private:
    ISerial_Communication* m_cmc;
    QTimer m_timer;
private slots:
    void onTimeout();
public:
    explicit ScanSerialTimer(QObject* parent = NULL);
};

#endif // _KUN__SCANSERIALTIMER_H_
