#ifndef _KUN__SERIAL_UI_H_
#define _KUN__SERIAL_UI_H_

#include "Serial_Communication.h"
#include "interface.h"
#include "Config.h"

#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QString>
#include <QColor>
#include <QStringList>
#include <QHBoxLayout>
#include <QStringList>
#include <QQueue>
#include "BluetoothAT_Window.h"

#define SENDSTRNUM 10

class SerialUI : public QWidget , public ISerialUI
{
    Q_OBJECT

private:
    QColor darkPurple;
    QColor deepIndigo;
    QColor lavender;
    QColor indigo;
    QColor brown;

    int m_sendCurrentNum;
    QQueue<QString> m_sendStrQueue;
    QString m_currentStr;

    QHBoxLayout* m_layout;
/*config_GBox***********************************************************************/
    QGroupBox m_config_GBox;

    QComboBox* m_comCbB;
    QComboBox* m_baudRateCbB;
    QComboBox* m_dataBitCbB;
    QComboBox* m_checkCbB;
    QComboBox* m_stopBitCbB;

    QPushButton* m_openSerialPBn;
    //QCheckBox*   m_DWPE_Cb;        //Disconnect without prompting error 断开不提示出错
    //QCheckBox*   m_EReconnectCb;   //Error reconnection  出错重连
/*assist_GBox************************************************************************/
    QGroupBox m_assist_GBox;

    QCheckBox* m_hexDisplayCb;
    QPushButton* m_ClearRecPBn;
    QPushButton* m_ClearCntPBn;
    QPushButton* m_BtAtPBn;
/*hotKey_GBox************************************************************************/
    QGroupBox m_hotKey_GBox;

    QPushButton* m_hotKey[HOTKEY_NUM];
/*recArea_GBox***********************************************************************/
    QGroupBox m_recArea_GBox;

    QTextEdit* m_recAreaTEd;
/*sendArea_GBox**********************************************************************/
    QGroupBox m_sendArea_GBox;

    QTextEdit* m_sendAreaTEd;
    QCheckBox* m_hexSendCb;
    QPushButton* m_ClearSendPBn;
    QPushButton* m_sendPBn;
/*sendArea_GBox**********************************************************************/
    QGroupBox m_BtAtWin_GBox;

    BluetoothAT_Window* m_BtAT_Window;
/*interface**************************************************************************/
    ISerial_Communication* m_cmc;
/*functions**************************************************************************/

    bool configMod_init();
    bool assistMod_init();
    bool hotKeyMod_init();
    bool recAreaMod_init();
    bool sendAreaMod_init();
    bool BtAtWinMod_init();
    bool group_init();
    bool shortcut_init();
    void Parameter_init();
    void connection();

    void addComboBoxItem();

    SerialUI();
    SerialUI(const SerialUI&);
    SerialUI& operator = (const SerialUI&);
    bool construct();
private slots:
    void onClearRecClicked();
    void onClearCntClicked();
    void onBtAtClicked();

    void onHotKeyLeftClicked();
    void onHotKeyRightClicked(QPushButton* obj);

    void onClearSendClicked();
    void onSendClicked();

    void onSendAreaUp();
    void onSendAreaDown();
protected:
    void closeEvent(QCloseEvent* evt);
    //void keyPressEvent(QKeyEvent * evt);
    bool eventFilter(QObject* obj, QEvent* e);
public:
    static SerialUI* NewInstance();

    void setMainWidgetColor(QWidget& window);
    void setGBoxColor(QGroupBox& gBox);
    void setTextEditColor(QTextEdit& TEdit);
    void setPushButtonColor(QPushButton& PBn);

    void addSerialComItem(const QStringList& comList);
    QString getCurrentSerialComName();
    long getBaudRate();
    int  getDataBit();
    int  getCheck();
    int  getStopBit();

    bool getIsHexDisplay();
    bool getIshexSend();

    void setRecAreaTitle(qint64 read, qint64 write);
    void setRecAreaText(const QString& text, bool isSend);
    void setSendAreaText(const QString& text);
    QString getSendAreaText();

    void isOpened(bool open);

    void setSerialCommunication(ISerial_Communication* cmc);
    ISerial_Communication* getSerialCommunication();

    ~SerialUI();
public slots:
    void onOpenSerialClicked();
};

#endif // _KUN__SERIAL_UI_H_
