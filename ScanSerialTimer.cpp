#include "ScanSerialTimer.h"
#include <QDebug>

ScanSerialTimer::ScanSerialTimer(QObject* parent)
    :m_cmc(dynamic_cast<ISerial_Communication*>(parent))
{
    if( m_cmc )
    {
        connect(&m_timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
        m_timer.start(200);
    }
    else
    {
        qDebug()<<"没有找到 ISerial_Communication";
    }
}

void ScanSerialTimer::onTimeout()
{
    //qDebug()<<"onTimeout";
    m_cmc->scanSerialPorts();
}
