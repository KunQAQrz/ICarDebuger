#ifndef _KUN__INTERFACE_H_
#define _KUN__INTERFACE_H_

#include <QStringList>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>

class ISerial_Communication
{
public:
    virtual void scanSerialPorts() = 0;
    virtual bool openSerialPort() = 0;
    virtual void closeSerialPort() = 0;
    virtual void clearBit() = 0;

    virtual void toSend() = 0;
    virtual void send(const QString& str) = 0;

    virtual ~ISerial_Communication() {}
};

class ISerialUI
{
public:
    virtual void addSerialComItem(const QStringList& comList) = 0;
    virtual QString getCurrentSerialComName() = 0;
    virtual long getBaudRate() = 0;
    virtual int  getDataBit() = 0;
    virtual int  getCheck() = 0;
    virtual int  getStopBit() = 0;
    virtual bool getIsHexDisplay() = 0;
    virtual bool getIshexSend() = 0;
    virtual void setRecAreaTitle(qint64 read, qint64 write) = 0;
    virtual void setRecAreaText(const QString& text, bool isSend) = 0;
    virtual void setSendAreaText(const QString& text) = 0;
    virtual QString getSendAreaText() = 0;
    virtual void isOpened(bool open) = 0;

    virtual void setMainWidgetColor(QWidget& window) = 0;
    virtual void setGBoxColor(QGroupBox& gBox) = 0;
    virtual void setTextEditColor(QTextEdit& TEdit) = 0;
    virtual void setPushButtonColor(QPushButton& PBn) = 0;

    virtual ~ISerialUI() {}
public slots:
    virtual void onOpenSerialClicked() = 0;
};

#endif // _KUN__INTERFACE_H_
