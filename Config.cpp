#include "Config.h"
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QApplication>

Config::Config()
{
    m_isValid = restore();
}

Config::Config( QSize   size        , QPoint  point,
                QString baudRate    , QString dataBit,
                QString check       , QString stopBit,
                bool    isHexDisplay, bool    isHexSend,
                QString* hotKeyName , QString* hotKeyContent )
    :
     m_mainWindowSize(size), m_mainWindowPoint(point),
     m_baudRate(baudRate), m_dataBit(dataBit),
     m_check(check), m_stopBit(stopBit),
     m_isHexDisplay(isHexDisplay), m_isHexSend(isHexSend),
     m_isValid(true)
{
    for(int i=0; i<HOTKEY_NUM; i++)
    {
        m_hotKeyName[i] = hotKeyName[i];
        m_hotKeyContent[i] = hotKeyContent[i];
    }
}

bool Config::restore()
{
    bool ret = false;

    bool res = true;
    QDir dir;
    QString dir_str = QApplication::applicationDirPath() + DIRNAME;
    if( !dir.exists(dir_str) )
    {
        res = dir.mkdir(dir_str);
    }
    if( res )
    {
        QFile file(dir_str + PATHNAME);
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_5_8);

            in >> m_mainWindowSize;
            in >> m_mainWindowPoint;
            in >> m_baudRate;
            in >> m_dataBit;
            in >> m_check;
            in >> m_stopBit;
            in >> m_isHexDisplay;
            in >> m_isHexSend;

            for(int i=0; i<HOTKEY_NUM; i++)
            {
                in >> m_hotKeyName[i];
                in >> m_hotKeyContent[i];
            }

            file.close();
            ret = true;
        }
    }

    return ret;
}

bool Config::store()
{
    bool ret = false;

    bool res = true;
    QDir dir;
    QString dir_str = QApplication::applicationDirPath() + DIRNAME;
    if( !dir.exists(dir_str) )
    {
        res = dir.mkdir(dir_str);
    }
    if( res )
    {
        QFile file(dir_str + PATHNAME);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_5_8);

            out << m_mainWindowSize;
            out << m_mainWindowPoint;
            out << m_baudRate;
            out << m_dataBit;
            out << m_check;
            out << m_stopBit;
            out << m_isHexDisplay;
            out << m_isHexSend;

            for(int i=0; i<HOTKEY_NUM; i++)
            {
                out << m_hotKeyName[i];
                out << m_hotKeyContent[i];
            }

            file.close();
            ret = true;
        }
    }

    return ret;
}

QSize Config::mainWindowSize()
{
    return m_mainWindowSize;
}

QPoint Config::mainWindowPoint()
{
    return m_mainWindowPoint;
}

QString Config::baudRate()
{
    return m_baudRate;
}

QString Config::dataBit()
{
    return m_dataBit;
}

QString Config::check()
{
    return m_check;
}

QString Config::stopBit()
{
    return m_stopBit;
}


bool Config::isHexDisplay()
{
    return m_isHexDisplay;
}

bool Config::isHexSend()
{
    return m_isHexSend;
}

QString* Config::hotKeyName()
{
    return m_hotKeyName;
}

QString* Config::hotKeyContent()
{
    return m_hotKeyContent;
}

bool Config::isValid()
{
    return m_isValid;
}
