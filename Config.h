#ifndef _KUN__CONFIG_H_
#define _KUN__CONFIG_H_

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QString>

#define HOTKEY_NUM 12

class Config : public QObject
{
    Q_OBJECT

    const QString DIRNAME = "/ICarDebuger Config";
    const QString PATHNAME = "/Parameter_Restoration.config";

    QSize  m_mainWindowSize;
    QPoint m_mainWindowPoint;

    QString m_baudRate;
    QString m_dataBit;
    QString m_check;
    QString m_stopBit;

    bool m_isHexDisplay;
    bool m_isHexSend;

    QString m_hotKeyName   [HOTKEY_NUM];
    QString m_hotKeyContent[HOTKEY_NUM];

    bool m_isValid;

    bool restore();
public:
    Config();

    explicit Config( QSize   size        , QPoint  point,
                     QString baudRate    , QString dataBit,
                     QString check       , QString stopBit,
                     bool    isHexDisplay, bool    isHexSend,
                     QString* hotKeyName , QString* hotKeyContent );
    bool store();

    QSize mainWindowSize();
    QPoint mainWindowPoint();

    QString baudRate();
    QString dataBit();
    QString check();
    QString stopBit();

    bool isHexDisplay();
    bool isHexSend();

    QString* hotKeyName();
    QString* hotKeyContent();

    bool isValid();
};

#endif // _KUN__CONFIG_H_
