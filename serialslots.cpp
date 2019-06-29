#include "SerialUI.h"
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include "MultipleInputDialog.h"
#include <QHBoxLayout>

/*serialConfig**********************************************/
void SerialUI::onOpenSerialClicked()
{
    static bool isOpen = false;
    qDebug() << "onOpenSerialClicked" ;
    if(m_cmc)
    {
        if(isOpen == false)
        {
            isOpen = !m_cmc->openSerialPort();
            qDebug() << "open";
        }
        else
        {
            m_cmc->closeSerialPort();
            qDebug() << "close";
        }

        isOpen = !isOpen;
    }
}
/***********************************************************/

/*serialAssist**********************************************/
void SerialUI::onClearRecClicked()
{
    qDebug() << "onClearRecClicked" ;
    m_recAreaTEd->clear();
}

void SerialUI::onClearCntClicked()
{
    qDebug() << "onClearCntClicked" ;

    m_cmc->clearBit();
}

void SerialUI::onBtAtClicked()
{
    qDebug() << "onBtAtClicked" ;

    static bool isVisible = false;

    if(m_layout)
    {
        if(!isVisible)
        {
            m_layout->addWidget(&m_BtAtWin_GBox);
        }
        else
        {
            m_layout->removeWidget(&m_BtAtWin_GBox);
            m_BtAtWin_GBox.setParent(NULL);
        }
        isVisible = !isVisible;
    }

}
/***********************************************************/

/*hotKey****************************************************/
bool SerialUI::eventFilter(QObject* obj, QEvent* e)
{
    bool ret = true;

    if( dynamic_cast<QMouseEvent*>(e) &&
        (e->type() == QEvent::MouseButtonRelease) &&
        (Qt::RightButton == dynamic_cast<QMouseEvent*>(e)->button()) )
    {
        for(int i=0; i<HOTKEY_NUM; i++)
        {
            if( obj == m_hotKey[i] )
            {
                emit onHotKeyRightClicked(dynamic_cast<QPushButton*>(obj));
                break;
            }
        }
    }

    else ret = QWidget::eventFilter(obj, e);


    return ret;
}

void SerialUI::onHotKeyLeftClicked()
{
    qDebug() << "onHotKeyLeftClicked" ;
    qDebug() << sender();
    if(m_sendPBn->isEnabled())
    {
        m_cmc->send(dynamic_cast<QPushButton*>(sender())->toolTip());
    }
    else
    {
        QMessageBox::warning(this,
                             "无法发送",
                             "串口没有打开!",
                             QMessageBox::Ok);
    }
}

void SerialUI::onHotKeyRightClicked(QPushButton* obj)
{
    qDebug() << "onHotKeyRightClicked" ;

    MultipleInputDialog mInputDialog(obj->text(),obj->toolTip(),this);

    if(mInputDialog.exec())
    {
        qDebug() << "set";
        qDebug() << mInputDialog.getName();
        obj->setText(mInputDialog.getName());
        obj->setToolTip(mInputDialog.getContent());
    }
}
/***********************************************************/

/*sendArea**************************************************/

void SerialUI::onClearSendClicked()
{
    qDebug() << "onClearSendClicked" ;
    m_sendAreaTEd->clear();
}

void SerialUI::onSendClicked()
{
    qDebug() << "onSendClicked" ;
    m_cmc->toSend();


    int index = m_sendStrQueue.indexOf(m_sendAreaTEd->toPlainText());
    if(-1 != index)
    {
        m_sendStrQueue.removeAt(index);
    }

    if(m_sendStrQueue.length() >= SENDSTRNUM)
    {
        m_sendStrQueue.dequeue();
    }

    m_sendStrQueue.enqueue(m_sendAreaTEd->toPlainText());
    m_sendCurrentNum = m_sendStrQueue.length();

    m_sendAreaTEd->clear();
}
/***********************************************************/

void SerialUI::onSendAreaUp()
{
    if( m_sendCurrentNum > 0 )
    {
        if( m_sendCurrentNum == m_sendStrQueue.length() )
        {
            m_currentStr = m_sendAreaTEd->toPlainText();
        }
        m_sendCurrentNum--;

        m_sendAreaTEd->setText(m_sendStrQueue[m_sendCurrentNum]);
    }
}

void SerialUI::onSendAreaDown()
{
    if( m_sendCurrentNum < m_sendStrQueue.length() )
    {
        m_sendCurrentNum++;
        if( m_sendCurrentNum == m_sendStrQueue.length() )
        {
            m_sendAreaTEd->setText(m_currentStr);
        }
        else
        {
            m_sendAreaTEd->setText(m_sendStrQueue[m_sendCurrentNum]);
        }
    }
}

/***********************************************************/
void SerialUI::closeEvent(QCloseEvent* evt)
{
    QString tmptxt[HOTKEY_NUM];
    QString tmptip[HOTKEY_NUM];

    for(int i=0; i<HOTKEY_NUM; i++)
    {
        tmptxt[i] = m_hotKey[i]->text();
        tmptip[i] = m_hotKey[i]->toolTip();
    }

    Config oldConfig;

    Config config(isMaximized() ? oldConfig.mainWindowSize()  : size(),
                  isMaximized() ? oldConfig.mainWindowPoint() : pos(),
                  m_baudRateCbB->currentText(), m_dataBitCbB->currentText(),
                  m_checkCbB->currentText()   , m_stopBitCbB->currentText(),
                  m_hexDisplayCb->isChecked() , m_hexSendCb->isChecked(),
                  tmptxt                      , tmptip);
    config.store();

    QWidget::closeEvent(evt);
}

/*void SerialUI::keyPressEvent(QKeyEvent * evt)
{
    if (evt->key() == (Qt::Key_Shift + Qt::Key_Return))
    {
        emit m_sendPBn->click();
        qDebug()<< "m_sendPBn->click";
    }
    QWidget::keyPressEvent(evt);
}*/
