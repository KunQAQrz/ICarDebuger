#ifndef _KUN__SERIAL_H_
#define _KUN__SERIAL_H_

#include "Serial_Communication.h"
#include "SerialUI.h"
#include "ScanSerialTimer.h"

class Serial
{
protected:
    SerialUI* m_ui;//将m_ui的dec接口对应到m_cmc

    Serial_Communication* m_cmc;

    Serial();
    bool construct();
public:
    static Serial* NewInstance();
    void show();
    ~Serial();
};

#endif // _KUN__SERIAL_H_
