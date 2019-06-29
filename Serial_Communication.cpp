#include "Serial_Communication.h"
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>
#include <QVariant>

Serial_Communication::Serial_Communication():m_ui(NULL),m_inUseSerialPort(NULL)
{
    readBit = 0;
    writeBit = 0;
}

Serial_Communication::~Serial_Communication()
{
    closeSerialPort();
}

void Serial_Communication::scanSerialPorts()
{
    QList<QSerialPortInfo> tmpComList = QSerialPortInfo::availablePorts();

    bool update = false;
    static int freq = 0;

    if(m_inUseSerialPort && m_inUseSerialPort->isOpen())
    {
        int i;
        for(i=0; i<tmpComList.length(); i++)
        {
            if( m_inUseSerialPort->portName() == tmpComList[i].portName() )
            {
                break;
            }
        }
        if( tmpComList.length() == i )
        {
            update = true;
            m_ui->onOpenSerialClicked();
        }
    }
    else if(m_comList.length() == tmpComList.length())
    {
        if(freq == 2)
        {
            for(int i=0; i<m_comList.length(); i++)
            {
                if((m_comList[i].portName())
                        != (tmpComList[i].portName()))
                {
                    update = true;
                    break;
                }
            }
        }
    }
    else update = true;

    if( update )
    {
        m_comList = tmpComList;

        m_serialPortsNameANDdec.clear();
        for(int i=0; i<m_comList.length(); i++)
        {
            m_serialPortsNameANDdec << m_comList[i].portName() + "\n" + m_comList[i].description();

            //qDebug()<< "serialPortName:"<<m_comList[i].portName() + "\n" + m_comList[i].description();
        }

        m_ui->addSerialComItem(m_serialPortsNameANDdec);
    }

    freq = (freq+1)%3;
}

bool Serial_Communication::openSerialPort()
{
    bool ret = false;

    closeSerialPort(); //如果串口已经打开了 先给他关闭了

    if( !m_inUseSerialPort )
    {
        m_inUseSerialPort = new QSerialPort();
    }

    qDebug()<<m_ui;
    qDebug()<<m_inUseSerialPort;

    if( m_ui && m_inUseSerialPort)
    {
        m_inUseSerialPort->setPortName(m_ui->getCurrentSerialComName());

        if(m_inUseSerialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            m_inUseSerialPort->setBaudRate(m_ui->getBaudRate(),QSerialPort::AllDirections);//设置波特率和读写方向
            m_inUseSerialPort->setDataBits(static_cast<QSerialPort::DataBits>(m_ui->getDataBit()));      //数据位为8位
            m_inUseSerialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
            m_inUseSerialPort->setParity(static_cast<QSerialPort::Parity>(m_ui->getCheck())); //无校验位
            m_inUseSerialPort->setStopBits(static_cast<QSerialPort::StopBits>(m_ui->getStopBit())); //一位停止位

            qDebug() << m_inUseSerialPort->portName();
            qDebug() << m_inUseSerialPort->dataBits();

            connect(m_inUseSerialPort,SIGNAL(readyRead()),this,SLOT(toRead()));

            m_ui->isOpened(true);
            ret = true;
        }
        else
        {
            qDebug() << "出错";
            QMessageBox::warning(dynamic_cast<SerialUI*>(m_ui),
                                 "警告",
                                 "串口没有初始化成功",
                                 QMessageBox::Ok);
        }
    }

    return ret;
}

void Serial_Communication::closeSerialPort()
{
    if(m_inUseSerialPort && m_inUseSerialPort->isOpen())
    {
        m_inUseSerialPort->clear();
        m_inUseSerialPort->close();
        delete m_inUseSerialPort;
        m_inUseSerialPort = NULL;
    }
    m_ui->isOpened(false);
}

void Serial_Communication::clearBit()
{
    readBit = 0;
    writeBit = 0;

    m_ui->setRecAreaTitle(readBit, writeBit);
}

void Serial_Communication::toRead()
{
    QByteArray buf;
    buf = m_inUseSerialPort->readAll();

    readBit += buf.length();

    m_ui->setRecAreaTitle(readBit,writeBit);

    displayRec(buf, false);
}

void Serial_Communication::toSend()
{
    if(m_inUseSerialPort && m_inUseSerialPort->isOpen())
    {
        QString tmpStr = m_ui->getSendAreaText();

        tmpStr.replace("\n","\r\n");

        send(tmpStr);
    }
}

void Serial_Communication::send(const QString& str)
{
    QByteArray tmpHex;
    if(!m_ui->getIshexSend())
    {
        QTextCodec *tc = QTextCodec::codecForName("GBK");
        tmpHex = tc->fromUnicode(str);
    }
    else
    {
        tmpHex = hexString2HexByteArray(str);
    }
    if(!tmpHex.isEmpty())
    {
        writeBit += m_inUseSerialPort->write(tmpHex);
        m_ui->setRecAreaTitle(readBit,writeBit);


        displayRec(tmpHex, true);
    }
}

QByteArray Serial_Communication::hexString2HexByteArray(QString hexStr)
{
    QByteArray ret;

    hexStr = hexStr.trimmed().simplified();

    qDebug()<<hexStr;
    for(int i=0; i<hexStr.length();)
    {
        QChar ch = hexStr[i];
        if( !
          (((ch >= '0') && (ch <= '9')) ||
           ((ch >= 'A') && (ch <= 'F')) ||
           ((ch >= 'a') && (ch <= 'f')) ))
        {
            hexStr.remove(i,1);
        }
        else  i++;
    }
    qDebug()<<hexStr;

    ret.resize(hexStr.length()/2);

    int len =0;
    for(int i=0; (i+1)<hexStr.length(); i+=2,len++)
    {
        int hHex = char2Hex(hexStr[i].toLatin1());
        int lHex = char2Hex(hexStr[i+1].toLatin1());

        ret[len] = static_cast<char>(hHex*16 + lHex);
    }
    ret.resize(len);

    return ret;
}

char Serial_Communication::char2Hex(char ch)
{
    if((ch >= '0') && (ch <= '9'))      return ch-0x30;
    if((ch >= 'A') && (ch <= 'F'))      return ch-'A'+10;
    if((ch >= 'a') && (ch <= 'f'))      return ch-'a'+10;

    return -1;
}

void Serial_Communication::displayRec(const QByteArray& buf, bool isSend)
{
    if(!m_ui->getIsHexDisplay())
    {
        QTextCodec *tc = QTextCodec::codecForName("GBK");
        QString tmpStr = tc->toUnicode(buf);
        m_ui->setRecAreaText(tmpStr, isSend);
        qDebug()<<tmpStr;
    }
    else
    {
        QString tmpHex = buf.toHex().toUpper();
        int len = tmpHex.length();

        for(int i=0; i<len; i++)
        {
            tmpHex.insert(2*i+i-1," ");
        }

        m_ui->setRecAreaText(tmpHex, isSend);
        qDebug()<<tmpHex;
    }
}

void Serial_Communication::setSerialUI(ISerialUI *ui)
{
    m_ui = ui;
}

ISerialUI *Serial_Communication::getSerialUI()
{
    return m_ui;
}
