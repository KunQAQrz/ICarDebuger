#include "Serial.h"

Serial::Serial():m_ui(NULL)
{

}

bool Serial::construct()
{
    m_ui = SerialUI::NewInstance();
    m_cmc = new Serial_Communication();
    bool ret = (m_ui != NULL) && (m_cmc != NULL);

    if( ret )
    {
        m_ui->setSerialCommunication(m_cmc);
        m_cmc->setSerialUI(m_ui);
        if(m_ui->getSerialCommunication() && m_cmc->getSerialUI())
        {
            m_ui->isOpened(false);
            m_cmc->scanSerialPorts();
            new ScanSerialTimer(m_cmc);
        }
    }

    return ret;
}

Serial* Serial::NewInstance()
{
    Serial* ret = new Serial;
    if( !ret || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void Serial::show()
{
    m_ui->show();
}

Serial::~Serial()
{
    delete m_ui;
    delete m_cmc;
}
