#ifndef _KUN__BLUETOOTHAT_CONFIG_H
#define _KUN__BLUETOOTHAT_CONFIG_H

#include <QObject>
#include <QQueue>

#define DEFARRLEN 14

struct AT
{
  QString name;
  QString instruct;
  QString tip;
};

class BluetoothAT_Config : public QObject
{
    Q_OBJECT

    const AT def[DEFARRLEN] =
    {
        {" 测试蓝牙 "   ,"AT\r\n"                        ,"AT波特率:38400,成功响应OK"},
        {" 查询蓝牙名字 ","AT+NAME?\r\n"                  ,""},
        {" 更改蓝牙名字 ","AT+NAME=名字\r\n"               ,""},
        {" 查询蓝牙密码 ","AT+PSWD?\r\n"                  ,""},
        {" 更改蓝牙密码 ","AT+PSWD=配对码\r\n"             ,"匹配码为四位数字"},
        {" 查询串口参数 ","AT+UART?\r\n"                  ,"波特率,停止位,校验位"},
        {" 更改串口参数 ","AT+UART=波特率,停止位,校验位\r\n" ,"校验位: 0:无,1:奇,2:偶"},
        {" 查询模块角色 ","AT+ROLE?\r\n"                  ,"0:从,1:主,2:回环"},
        {" 更改模块角色 ","AT+ROLE=角色\r\n"               ,"0:从,1:主,2:回环"},
        {" 查询蓝牙地址 ","AT+ADDR?\r\n"                  ,""},
        {" 查询帮助 ","AT+HELP\r\n"                      ,""},
        {" 蓝牙复位 ","AT+RESET\r\n"                     ,""},
        {" 恢复默认状态 ","AT+ORGL\r\n"                   ,"默认从角色"},
        {" 软件版本号 ","AT+VERSION?\r\n"                 ,""}
    };

    const QString DIRNAME = "/ICarDebuger Config";
    const QString PATHNAME = "/BluetoothAT_Config.txt";

    QQueue<AT> m_data;

    bool restore();
    bool store();
public:
    BluetoothAT_Config();
    const QQueue<AT>& getATdata();
};

#endif // _KUN__BLUETOOTHAT_CONFIG_H
