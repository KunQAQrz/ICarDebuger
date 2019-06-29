#ifndef _KUN__SERIAL_COMMUNICATION_H_
#define _KUN__SERIAL_COMMUNICATION_H_

#include "interface.h"
#include "SerialUI.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QList>

class Serial_Communication : public QObject,public ISerial_Communication
{
    Q_OBJECT
private:
    ISerialUI* m_ui;

    qint64 readBit;
    qint64 writeBit;

    QList<QSerialPortInfo> m_comList;
    QStringList m_serialPortsNameANDdec;
    QSerialPort* m_inUseSerialPort;

    QByteArray hexString2HexByteArray(QString hexStr);
    char char2Hex(char ch);
    void displayRec(const QByteArray& buf, bool isSend);
private slots:
    void toRead();
public:
    Serial_Communication();
    void scanSerialPorts();
    bool openSerialPort();
    void closeSerialPort();
    void clearBit();

    void toSend();
    void send(const QString& str);

    void setSerialUI(ISerialUI* ui);
    ISerialUI* getSerialUI();

    virtual ~Serial_Communication();
};

#endif // _KUN__SERIAL_COMMUNICATION_H_
