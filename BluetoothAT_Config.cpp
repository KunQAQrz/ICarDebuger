#include "BluetoothAT_Config.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QApplication>

BluetoothAT_Config::BluetoothAT_Config()
{
    if(QFile::exists(QApplication::applicationDirPath() + DIRNAME + PATHNAME))
    {
        restore();
    }
    else
    {
        store();
    }
}

bool BluetoothAT_Config::restore()
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
        QFile file( dir_str + PATHNAME);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);

            while( !in.atEnd() )
            {
                QString line = in.readLine();

                if(line != "")
                {
                    QStringList ATstrList = line.trimmed().split(";");
                    AT tmpAT = {" " + ATstrList[0] + " ", ATstrList[1] + "\r\n", ATstrList[2]};

                    m_data.append(tmpAT);
                }
            }

            file.close();
            ret = true;
        }
    }

    return ret;
}

bool BluetoothAT_Config::store()
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
        QFile file( dir_str + PATHNAME);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);

            for(int i=0; i<DEFARRLEN; i++)
            {
                m_data.append(def[i]);

                out << def[i].name.trimmed()        << ";";
                out << def[i].instruct.simplified() << ";";
                out << def[i].tip                   << "\r\n\r\n";
            }

            file.close();
            ret = true;
        }
    }

    return ret;
}

const QQueue<AT>& BluetoothAT_Config::getATdata()
{
    return m_data;
}
