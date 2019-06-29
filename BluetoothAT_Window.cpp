#include "BluetoothAT_Window.h"
#include "BluetoothAT_Config.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

BluetoothAT_Window::BluetoothAT_Window(QWidget* parent, ISerialUI* ui)
    : QWidget(parent),  m_ui(ui)
{
    BluetoothAT_Config ATconfig;
    const QQueue<AT> tmpQue = ATconfig.getATdata();

    m_fLayout = new QFormLayout(this);

    if(m_ui && m_fLayout)
    {
        QPushButton* pbn[tmpQue.length()];
        for(int i=0; i<tmpQue.length(); i++)
        {
            pbn[i] = new QPushButton(tmpQue[i].name,this);
            if( pbn[i] )
            {
                pbn[i]->setWindowTitle(tmpQue[i].instruct);
                qDebug()<< pbn[i]->windowTitle();
                pbn[i]->setToolTip(tmpQue[i].tip);
                //pbn[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

                m_ui->setPushButtonColor(*pbn[i]);

                m_fLayout->addRow(pbn[i]);

                connect(pbn[i],SIGNAL(clicked()),this,SLOT(onATclicked()));
            }
        }

        QPushButton* about = new QPushButton("关于",this);
        if(about)
        {
            m_ui->setPushButtonColor(*about);
            m_fLayout->addRow(about);
            connect(about,SIGNAL(clicked()),this,SLOT(onAbouted()));
        }

        setLayout(m_fLayout);
    }
}

void BluetoothAT_Window::onATclicked()
{
    qDebug()<<dynamic_cast<QPushButton*>(sender())->windowTitle();
    m_ui->setSendAreaText(dynamic_cast<QPushButton*>(sender())->windowTitle());
}

void BluetoothAT_Window::onAbouted()
{
    QMessageBox::about(this,
                       "关于",
                       "作者:沈兆坤   \r\n\r\n版本:α1.2");
}
