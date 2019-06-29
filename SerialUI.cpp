#include "SerialUI.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include <QScrollArea>
#include <QDebug>
#include <QShortcut>

SerialUI* SerialUI::NewInstance()
{
    SerialUI* ret = new SerialUI();
    if( !ret || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

bool SerialUI::construct()
{
    bool ret = true;

    ret &= configMod_init();

    ret &= assistMod_init();

    ret &= hotKeyMod_init();

    ret &= recAreaMod_init();

    ret &= sendAreaMod_init();

    ret &= BtAtWinMod_init();

    ret &= group_init();

    ret &= shortcut_init();

    Parameter_init();

    connection();

    return ret;
}

SerialUI::SerialUI() : m_layout(NULL),m_cmc(NULL)
{
    darkPurple = QColor( 32, 29, 54);
    //deepIndigo = QColor( 30, 30, 39);
    deepIndigo = QColor( 19, 19, 26);
    lavender   = QColor(139,139,205);
    indigo     = QColor( 62, 59, 81);
    brown      = QColor(207,191,173);

    setWindowTitle("ICarDebuger α1.2");
    setMinimumSize(830, 720);
    m_sendCurrentNum = m_sendStrQueue.length();
    //setStyleSheet("QGroupBox{border:none}");

    setMainWidgetColor(*this);

    m_config_GBox.setParent(this);
    m_assist_GBox.setParent(this);
    m_hotKey_GBox.setParent(this);
    m_recArea_GBox.setParent(this);
    m_sendArea_GBox.setParent(this);
    m_BtAtWin_GBox.setParent(this);

    m_config_GBox.setTitle("串口配置");
    m_assist_GBox.setTitle("串口辅助");
    m_hotKey_GBox.setTitle("热键");
    m_recArea_GBox.setTitle("接收区: 共接收 0 字节，共发送 0 字节");
    m_sendArea_GBox.setTitle("发送区");
    m_BtAtWin_GBox.setTitle("At指令");

    setGBoxColor(m_config_GBox);
    setGBoxColor(m_assist_GBox);
    setGBoxColor(m_hotKey_GBox);
    setGBoxColor(m_recArea_GBox);
    setGBoxColor(m_sendArea_GBox);
    setGBoxColor(m_BtAtWin_GBox);

    m_sendArea_GBox.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
}

SerialUI::~SerialUI()
{

}

bool SerialUI::configMod_init()
{
    bool ret = true;
    QVBoxLayout* vLayout = new QVBoxLayout;
    QFormLayout* fLayout = new QFormLayout;

    ret = (vLayout && fLayout);
    if( ret )
    {
        m_comCbB      = new QComboBox(&m_config_GBox);
        m_baudRateCbB = new QComboBox(&m_config_GBox);
        m_dataBitCbB  = new QComboBox(&m_config_GBox);
        m_checkCbB    = new QComboBox(&m_config_GBox);
        m_stopBitCbB  = new QComboBox(&m_config_GBox);

        m_openSerialPBn = new QPushButton(/*"打开串口",*/&m_config_GBox);

        //m_DWPE_Cb       = new QCheckBox("断开不提示出错",&m_config_GBox);
        //m_EReconnectCb  = new QCheckBox("出错重连",&m_config_GBox);

        ret = ( m_comCbB && m_baudRateCbB && m_dataBitCbB &&
                m_checkCbB && m_stopBitCbB && m_openSerialPBn /*&&
                m_DWPE_Cb && m_EReconnectCb*/);

        if( ret )
        {
            setPushButtonColor(*m_openSerialPBn);

            addComboBoxItem();

            fLayout->addRow("端口: ",m_comCbB);
            fLayout->addRow("波特率:",m_baudRateCbB);
            fLayout->addRow("数据位:",m_dataBitCbB);
            fLayout->addRow("校验: ",m_checkCbB);
            fLayout->addRow("停止位:",m_stopBitCbB);

            vLayout->addLayout(fLayout);
            vLayout->addWidget(m_openSerialPBn);
            //vLayout->addWidget(m_DWPE_Cb);
            //vLayout->addWidget(m_EReconnectCb);

            m_comCbB->setMaximumWidth(80);
            //m_openSerialPBn->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);

            m_config_GBox.setLayout(vLayout);
        }
    }

    return ret;
}

bool SerialUI::assistMod_init()
{
    bool ret = true;

    QVBoxLayout* vLayout = new QVBoxLayout;

    ret = vLayout;
    if( ret )
    {
        m_hexDisplayCb = new QCheckBox("16进制显示",&m_assist_GBox);
        m_ClearRecPBn  = new QPushButton("清空接收区",&m_assist_GBox);
        m_ClearCntPBn  = new QPushButton("清空统计",&m_assist_GBox);
        m_BtAtPBn      = new QPushButton("蓝牙AT指令",&m_assist_GBox);

        ret = ( m_hexDisplayCb && m_ClearRecPBn && m_ClearCntPBn
                && m_BtAtPBn );

        if( ret )
        {
            setPushButtonColor(*m_ClearRecPBn);
            setPushButtonColor(*m_ClearCntPBn);
            setPushButtonColor(*m_BtAtPBn);

            vLayout->addWidget(m_hexDisplayCb);
            vLayout->addWidget(m_ClearRecPBn);
            vLayout->addWidget(m_ClearCntPBn);
            vLayout->addWidget(m_BtAtPBn);

            m_assist_GBox.setLayout(vLayout);

        }
    }

    return ret;
}

bool SerialUI::hotKeyMod_init()
{
    bool ret = true;
    const int COL = 2;

    QGridLayout* gLayout = new QGridLayout;

    for(int i=0; (i<HOTKEY_NUM) && ret; i++)
    {
        m_hotKey[i] = new QPushButton(&m_hotKey_GBox);

        ret = m_hotKey[i];
        if( ret )
        {
            m_hotKey[i]->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
            setPushButtonColor(*m_hotKey[i]);
            gLayout->addWidget(m_hotKey[i], i/COL, (i+COL)%COL);
        }
    }

    if( ret )
    {
        m_hotKey_GBox.setLayout(gLayout);
    }

    return ret;
}

bool SerialUI::recAreaMod_init()
{
    bool ret = true;

    QHBoxLayout* hLayout = new QHBoxLayout;

    ret = hLayout;
    if( ret )
    {
         m_recAreaTEd = new QTextEdit(&m_recArea_GBox);

         ret = m_recAreaTEd;
         if( ret )
         {
             m_recAreaTEd->setReadOnly(true);
             setTextEditColor(*m_recAreaTEd);
             hLayout->addWidget(m_recAreaTEd);

             m_recArea_GBox.setLayout(hLayout);
         }
    }

    return ret;
}

bool SerialUI::sendAreaMod_init()
{
    bool ret = true;

    QGridLayout* gLayout = new QGridLayout;

    ret = gLayout;
    if( ret )
    {
         m_sendAreaTEd  = new QTextEdit(&m_sendArea_GBox);
         m_hexSendCb    = new QCheckBox("16进制发送",&m_sendArea_GBox);
         m_ClearSendPBn = new QPushButton("清空发送区",&m_sendArea_GBox);
         m_sendPBn      = new QPushButton("发送",&m_sendArea_GBox);

         ret = ( m_sendAreaTEd && m_hexSendCb && m_ClearSendPBn &&
                 m_sendPBn );
         if( ret )
         {
             setTextEditColor(*m_sendAreaTEd);
             setPushButtonColor(*m_ClearSendPBn);
             setPushButtonColor(*m_sendPBn);

             gLayout->addWidget(m_sendAreaTEd,0,0,1,4);
             gLayout->addWidget(m_hexSendCb,1,0);
             gLayout->addWidget(m_ClearSendPBn,1,2);
             gLayout->addWidget(m_sendPBn,1,3);

             m_sendArea_GBox.setLayout(gLayout);
         }
    }

    return ret;
}

bool SerialUI::BtAtWinMod_init()
{
    bool ret = true;

    QScrollArea* scrolArea = new QScrollArea(&m_BtAtWin_GBox);

    QVBoxLayout* vLayout = new QVBoxLayout;

    ret = (vLayout && scrolArea);

    if( ret )
    {
        m_BtAT_Window = new BluetoothAT_Window(scrolArea,this);
        ret = m_BtAT_Window;
        if( ret )
        {
            scrolArea->setWidget(m_BtAT_Window);
            scrolArea->setAlignment(Qt::AlignHCenter);
            scrolArea->setMinimumWidth(145);
            scrolArea->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
            vLayout->addWidget(scrolArea);

            m_BtAtWin_GBox.setLayout(vLayout);
            m_BtAtWin_GBox.setParent(NULL);
        }
    }

    return ret;
}

bool SerialUI::group_init()
{
    bool ret = true;

    m_layout = new QHBoxLayout;
    QGridLayout* gLayout = new QGridLayout;

    ret = (m_layout && gLayout);
    if( ret )
    {
        gLayout->addWidget(&m_config_GBox,0,0);
        gLayout->addWidget(&m_assist_GBox,1,0);
        gLayout->addWidget(&m_hotKey_GBox,3,0,3,1);
        gLayout->addWidget(&m_recArea_GBox,0,1,4,2);
        gLayout->addWidget(&m_sendArea_GBox,4,1,2,1);

        m_layout->addLayout(gLayout);
        setLayout(m_layout);
    }

    return ret;
}

bool SerialUI::shortcut_init()
{
    bool ret = true;

    m_sendPBn->setFocus();
    m_sendPBn->setShortcut( QKeySequence(Qt::SHIFT + Qt::Key_Enter) );

    QShortcut* keyUp   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up),this);
    QShortcut* keyDown = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down),this);

    ret = (keyUp && keyDown);
    if( ret )
    {
        connect(keyUp  , SIGNAL(activated()), this, SLOT(onSendAreaUp()));
        connect(keyDown, SIGNAL(activated()), this, SLOT(onSendAreaDown()));
    }
    return ret;
}

void SerialUI::Parameter_init()
{
    Config config;
    if( config.isValid() )
    {
        resize(config.mainWindowSize());
        move(config.mainWindowPoint());

        m_baudRateCbB->setCurrentText(config.baudRate());
        m_dataBitCbB->setCurrentText(config.dataBit());
        m_checkCbB->setCurrentText(config.check());
        m_stopBitCbB->setCurrentText(config.stopBit());

        m_hexDisplayCb->setChecked(config.isHexDisplay());
        m_hexSendCb->setChecked(config.isHexSend());

        for(int i=0; i<HOTKEY_NUM; i++)
        {
            m_hotKey[i]->setText(config.hotKeyName()[i]);
            m_hotKey[i]->setToolTip(config.hotKeyContent()[i]);
        }
    }
    else
    {
        const QString str_hotKey[HOTKEY_NUM] =
        {
            "1" ,"2" ,"3",
            "4" ,"5" ,"6",
            "7" ,"8" ,"9",
            "10","11","12",
        };

        m_baudRateCbB->setCurrentText("115200");
        m_dataBitCbB->setCurrentText("8");

        for(int i=0; i<HOTKEY_NUM; i++)
        {
            m_hotKey[i]->setText(str_hotKey[i]);
        }
    }
}

void SerialUI::connection()
{  
    connect(m_openSerialPBn,SIGNAL(clicked()),this,SLOT(onOpenSerialClicked()));

    connect(m_ClearRecPBn,SIGNAL(clicked()),this,SLOT(onClearRecClicked()));
    connect(m_ClearCntPBn,SIGNAL(clicked()),this,SLOT(onClearCntClicked()));
    connect(m_BtAtPBn,SIGNAL(clicked()),this,SLOT(onBtAtClicked()));

    for(int i=0; i<HOTKEY_NUM; i++)
    {
        connect(m_hotKey[i],SIGNAL(clicked()),this,SLOT(onHotKeyLeftClicked()));
        m_hotKey[i]->installEventFilter(this);
    }

    connect(m_ClearSendPBn,SIGNAL(clicked()),this,SLOT(onClearSendClicked()));

    connect(m_sendPBn,SIGNAL(clicked()),this,SLOT(onSendClicked()));
}

void SerialUI::addComboBoxItem()
{
    m_baudRateCbB->addItem("1200");
    m_baudRateCbB->addItem("2400");
    m_baudRateCbB->addItem("4800");
    m_baudRateCbB->addItem("9600");
    m_baudRateCbB->addItem("11400");
    m_baudRateCbB->addItem("19200");
    m_baudRateCbB->addItem("38400");
    m_baudRateCbB->addItem("56000");
    m_baudRateCbB->addItem("57600");
    m_baudRateCbB->addItem("115200");
    m_baudRateCbB->addItem("128000");
    m_baudRateCbB->addItem("256000");

    m_dataBitCbB->addItem("5");
    m_dataBitCbB->addItem("6");
    m_dataBitCbB->addItem("7");
    m_dataBitCbB->addItem("8");

    m_checkCbB->addItem("无");
    m_checkCbB->addItem("奇校验");
    m_checkCbB->addItem("偶校验");

    m_stopBitCbB->addItem("1");
    m_stopBitCbB->addItem("2");
}

void SerialUI::addSerialComItem(const QStringList& comList)
{
    QString tmp = m_comCbB->currentText();
    m_comCbB->clear();
    m_comCbB->addItems(comList);
    m_comCbB->setCurrentText(tmp);
}

QString SerialUI::getCurrentSerialComName()
{
    return m_comCbB->currentText().split("\n")[0];
}

long SerialUI::getBaudRate()
{
      return m_baudRateCbB->currentText().toLong();
}

int SerialUI::getDataBit()
{
    return m_dataBitCbB->currentText().toInt();
}

int SerialUI::getCheck()
{
    QString text = m_checkCbB->currentText();

    if( text == "无" )     return QSerialPort::NoParity;

    if( text == "奇校验" )  return QSerialPort::EvenParity;

    if( text == "偶校验" )  return QSerialPort::OddParity;

    return QSerialPort::UnknownParity;
}

int SerialUI::getStopBit()
{
    return m_stopBitCbB->currentText().toInt();
}

bool SerialUI::getIsHexDisplay()
{
    return m_hexDisplayCb->isChecked();
}

bool SerialUI::getIshexSend()
{
    return m_hexSendCb->isChecked();
}

void SerialUI::setRecAreaTitle(qint64 read, qint64 write)
{
    char title[49] = "";
    sprintf(title,"接收区: 共接收 %lld 字节,共发送 %lld 字节", read, write);
    m_recArea_GBox.setTitle(title);
}

void SerialUI::setRecAreaText(const QString& text, bool isSend)
{
    if( isSend )
    {
        m_recAreaTEd->append(text);
    }
    else
    {
        m_recAreaTEd->insertPlainText(text);
    }
    m_recAreaTEd->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}

void SerialUI::setSendAreaText(const QString& text)
{
    m_sendAreaTEd->append(text);
    qDebug()<<m_sendAreaTEd->toPlainText();
}

QString SerialUI::getSendAreaText()
{
    return m_sendAreaTEd->toPlainText();
}

void SerialUI::isOpened(bool open)
{
    switch(static_cast<int>(open))
    {
        case true:
        {
            m_openSerialPBn->setText("关闭串口");

            m_comCbB->setDisabled(true);
            m_baudRateCbB->setDisabled(true);
            m_dataBitCbB->setDisabled(true);
            m_checkCbB->setDisabled(true);
            m_stopBitCbB->setDisabled(true);
            m_sendPBn->setDisabled(false);
        }
        break;

        case false:
        {
        m_openSerialPBn->setText("打开串口");

        m_comCbB->setDisabled(false);
        m_baudRateCbB->setDisabled(false);
        m_dataBitCbB->setDisabled(false);
        m_checkCbB->setDisabled(false);
        m_stopBitCbB->setDisabled(false);
        m_sendPBn->setDisabled(true);
        }
        break;
    }
}

void SerialUI::setMainWidgetColor(QWidget& window)
{
    QPalette p = window.palette();

    p.setColor(QPalette::Active  , QPalette::Background, darkPurple);
    p.setColor(QPalette::Inactive, QPalette::Background, darkPurple);
    p.setColor(QPalette::Active  , QPalette::WindowText, brown);
    p.setColor(QPalette::Inactive, QPalette::WindowText, brown);

    window.setPalette(p);
}

void SerialUI::setGBoxColor(QGroupBox& gBox)
{
    QPalette p = gBox.palette();

    p.setColor(QPalette::Active  , QPalette::Foreground, brown);
    p.setColor(QPalette::Inactive, QPalette::Foreground, brown);

    gBox.setPalette(p);
}

void SerialUI::setTextEditColor(QTextEdit& TEdit)
{
    QPalette p = TEdit.palette();

    p.setColor(QPalette::Active  , QPalette::Base, deepIndigo);
    p.setColor(QPalette::Inactive, QPalette::Base, deepIndigo);
    p.setColor(QPalette::Active  , QPalette::Text, brown);
    p.setColor(QPalette::Inactive, QPalette::Text, brown);
    p.setColor(QPalette::Active  , QPalette::Highlight, lavender);
    p.setColor(QPalette::Inactive, QPalette::Highlight, lavender);
    p.setColor(QPalette::Active  , QPalette::HighlightedText, deepIndigo);
    p.setColor(QPalette::Inactive, QPalette::HighlightedText, deepIndigo);

    //TEdit.setStyleSheet("QPushButton:focus{background-color:rgb(62, 59, 81);}");

    TEdit.setPalette(p);
}

void SerialUI::setPushButtonColor(QPushButton& PBn)
{
    QPalette p = PBn.palette();

    PBn.setStyleSheet("QPushButton{background-color:rgb(30, 30, 39);"\
    "border-radius: 13px;  border: 2px rgb(50, 0, 100);"\
    "border-style: outset;height: 25px}"\
    "QPushButton:hover{background-color:rgb(62, 59, 81);}"\
    "QPushButton:pressed{background-color:rgb(139,139,205); color: rgb(30, 30, 39);"\
    "border-style: inset; }");

    /*PBn.setStyleSheet("QPushButton{background-color:rgb(30, 30, 39);"\
    "border-radius: 13px;  border: 2px rgb(32, 29, 54);"\
    "border-style: outset;height: 25px}"\
    "QPushButton:hover{background-color:rgb(62, 59, 81);}"\
    "QPushButton:pressed{background-color:rgb(139,139,205); color: rgb(30, 30, 39);"\
    "border-style: inset; }");*/

    /*darkPurple = QColor( 32, 29, 54);
      deepIndigo = QColor( 30, 30, 39);
      lavender   = QColor(139,139,205);
      indigo     = QColor( 62, 59, 81);
      brown      = QColor(207,191,173);*/

    p.setColor(QPalette::Active  , QPalette::ButtonText, brown);
    p.setColor(QPalette::Inactive, QPalette::ButtonText, brown);
    p.setColor(QPalette::Disabled, QPalette::ButtonText, indigo);

    PBn.setPalette(p);
}

void SerialUI::setSerialCommunication(ISerial_Communication* cmc)
{
    m_cmc = cmc;
}

ISerial_Communication* SerialUI::getSerialCommunication()
{
    return m_cmc;
}
